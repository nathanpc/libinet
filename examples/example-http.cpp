/**
 * example-http.cpp
 * An example of how to do HTTP requests with the awesome libinet++ library.
 *
 * \author Nathan Campos
 */

#include <iostream>
#include <string>
#include <vector>

#include "../src/http.h"
using namespace std;

int main(int argc, char *argv[]) {
	// Setup the connection.
	HTTP http("localhost", 80);
	HTTP_Response response;

	http.add_header("User-Agent", "libinet++/0.1");
	response = http.request("POST", "/~Nathan/test_req.php", "Testing the POST body stuff.");

	// Print the raw response.
	//cout << response.raw << endl;

	// Print the response status (hope it's 200 OK).
	cout << response.status_code << " " << response.status_message << endl;

	// Print the headers.
	for (size_t i = 0; i < response.headers.size(); i++) {
		vector<string> header = response.headers.at(i);
		cout << header.at(0) << ": " << header.at(1) << endl;
	}

	// Print body.
	cout << endl << response.body << endl;

	return 0;
}
