/**
 * example-uri.cpp
 * An example of how to use the URI class from the awesome libinet++ library.
 *
 * \author Nathan Campos
 */

#include <iostream>
#include <string>
#include <vector>

#include "../src/uri.h"
using namespace std;

int main(int argc, char *argv[]) {
	URI uri("http://test.com/awesome.php?testing=true&another=test");

	// Print the protocol.
	cout << "Protocol: " << uri.protocol << endl;

	// Print the server.
	cout << "Server: " << uri.server << endl;

	// Print port.
	cout << "Port: " << uri.port << endl;

	// Print the location.
	cout << "Location: " << uri.location << endl;
	cout << "Full Location: " << uri.get_full_location() << endl;

	// Print all the params.
	for (size_t i = 0; i < uri.params.size(); i++) {
		cout << "Param: " << uri.params[i][0] << " = " << uri.params[i][1] << endl;
	}

	return 0;
}
