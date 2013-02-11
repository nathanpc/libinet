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

	http.add_header("User-Agent", "libinet++/0.1");
	response = http.request("/~Nathan/test_req.php");
	cout << response.raw << endl;

	return 0;
}
