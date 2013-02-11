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

#include "sockets.h"

#define MAXDATASIZE 1024  // Max number of bytes we can get at once.
using namespace std;

/**
 * Constructs the Socket object and connect to the server
 *
 * \param server The server location.
 * \param port The server port.
 */
Socket::Socket(string server, string port) {
	struct addrinfo hints, *servinfo;
	int res;
	connected = false;

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
			cerr << "An error occuried while trying to close the connection" << endl;
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
		cerr << "An error occuried while trying to send the data" << endl;
		exit(EXIT_FAILURE);
	}

	return bytes_sent;
}
