/**
 * example-http.cpp
 * An example of how to do HTTP requests with the awesome libinet++ library.
 *
 * \author Nathan Campos
 */

#include <iostream>
#include <string>

#include "../src/http.h"
using namespace std;

int main(int argc, char *argv[]) {
	// Setup the connection.
	HTTP http("localhost", 80);
	HTTP_Response response;

	response = http.request("/");
	cout << response.raw << endl;

	return 0;
}
