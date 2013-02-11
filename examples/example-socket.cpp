/**
 * example-socket.cpp
 * An example of how to use sockets with the awesome libinet++ library.
 *
 * \author Nathan Campos
 */

#include <iostream>
#include <string>

#include "../src/sockets.h"
using namespace std;

bool socket_data_callback(string data) {
	// If something went wrong while you were parsing return false!
	cout << data << endl;
	return true;
}

int main(int argc, char *argv[]) {
	// Setup the socket and connect.
	Socket socket("localhost", 80, &socket_data_callback);
	socket.connect();

	// Send some information.
	socket.send_data("GET / HTTP/1.1\r\n");
	socket.send_data("Host: localhost\r\n\r\n");

	// Get the response.
	socket.receive();

	return 0;
}
