/**
 *  sockets.cpp
 *  Raw internet sockets.
 *
 *  \author Nathan Campos <nathanpc@dreamintech.net>
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "sockets.h"

#define MAXDATASIZE 1024  // Max number of bytes we can get at once.
using namespace std;

/**
 * Constructs the Socket object and connect to the server
 *
 * \param server The server location.
 * \param port The server port.
 * \param _handler_callback Callback to parse the received information.
 */
Socket::Socket(string server, string port, HandlerCallback _handler_callback) {
	connected = false;
	handler_callback = _handler_callback;

	struct addrinfo hints, *servinfo;
	int res;

	// Empty the hints struct and setup.
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	// Setup the structs.
	res = getaddrinfo(server.c_str(), port.c_str(), &hints, &servinfo);
	if (res != 0) {
		cerr << "getaddrinfo: " << gai_strerror(res) << endl;
		exit(EXIT_FAILURE);
	}

	// Setup the socket.
	socket_descriptor = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
	if (socket_descriptor == -1) {
		cerr << "Couldn't setup socket." << endl;
		exit(EXIT_FAILURE);
	}

	// Connect.
	if (connect(socket_descriptor, servinfo->ai_addr, servinfo->ai_addrlen) == -1) {
		close(socket_descriptor);

		cerr << "Couldn't connect to host." << endl;
	} else {
		connected = true;

		// Create the thread that will handle messages from the server
		pthread_create(&thread, NULL, &handle_recv_thread_helper, this);
	}

	// Free the server information.
	freeaddrinfo(servinfo);
}

/**
 * Closes the connection if it's connected.
 */
void Socket::close_connection() {
	if (connected) {
		if (close(socket_descriptor) != 0) {
			cerr << "An error occurred while trying to close the connection" << endl;
			exit(EXIT_FAILURE);
		}

		connected = false;
	}
}

/**
 * Send the data string to the server.
 *
 * \return Number of bytes sent.
 */
int Socket::send_data(string data) {
	const char *buffer = data.c_str();
	int len = strlen(buffer);
	int bytes_sent = send(socket_descriptor, buffer, len, 0);

	if (bytes_sent == -1) {
		cerr << "An error occurred while trying to send the data" << endl;
		exit(EXIT_FAILURE);
	}

	return bytes_sent;
}

/**
 * Just a little hack to make pthread work with a C++ class.
 */
void *Socket::handle_recv_thread_helper(void *context) {
	return ((Socket *)context)->handle_recv();
}

/**
 * Handles the information that was received from the server.
 */
void *Socket::handle_recv() {
	// recv some data.
	int numbytes;
	char buffer[MAXDATASIZE];
	static string sbuf;
	size_t pos;

	numbytes = recv(socket_descriptor, buffer, MAXDATASIZE - 1, 0);
	while (numbytes > 0) {
		// NULL-terminate the buffer
		buffer[numbytes] = '\0';

		// Append the buffer instead of assigning so we don't lose anything
		sbuf += buffer;

		// Search for the CR (\r) character followed by the LF (\n) character,
		while ((pos = sbuf.find("\r\n")) != string::npos) {
			// Copy the whole message, including the CRLF at the end
			string msg = sbuf.substr(0, pos + 2);

			// Erase the msg from sbuf
			sbuf.erase(0, msg.size());

			// Handle the received message
			if (!handler_callback(msg)) {
				connected = false;
				return NULL;
			}
		}
	}

	// Check if there was an error
	if (numbytes == -1) {
		cerr << "handle_recv Error" << endl;
		exit(EXIT_FAILURE);
	}

	connected = false;
	return NULL;
}
