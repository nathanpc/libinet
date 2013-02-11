/**
 *  sockets.cpp
 *  Raw internet sockets.
 *
 *  Nathan Campos <nathanpc@dreamintech.net>
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


Socket::Socket(string server, string port) {
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
		exit(1);
	}

	// Setup the socket.
	socket_descriptor = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
	if (socket_descriptor == -1) {
		cerr << "Couldn't setup socket." << endl;
		exit(1);
	}

	if (connect(socket_descriptor, servinfo->ai_addr, servinfo->ai_addrlen) == -1) {
		close(socket_descriptor);

		cerr << "Couldn't connect to host." << endl;
		exit(1);
	}
}
