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

void progress(size_t length, size_t received_length) {
	cout << (received_length * 100) / length << "%" << endl;
}

int main(int argc, char *argv[]) {
	// Setup the connection.
	HTTP http("localhost", 80);
	HTTP_Response response;

	http.add_header("User-Agent", "libinet++/0.1");
	http.set_progress_callback(&progress);  // Optional

	response = http.request("POST", "/test.php", "Test POST body");

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
