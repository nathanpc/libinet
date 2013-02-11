/**
 *  http.cpp
 *  HTTP client for human C++ developers.
 *
 *  Nathan Campos <nathanpc@dreamintech.net>
 */

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "http.h"
#include "sockets.h"
using namespace std;

string HTTP::raw_response = "";

/**
 * HTTP_Response class constructor.
 */
HTTP_Response::HTTP_Response() {
	string raw = "";
	string body = "";
}

/**
 * HTTP class constructor.
 */
HTTP::HTTP() {
	HTTP::raw_response = "";
}

/**
 * HTTP class constructor.
 *
 * \param _server Server URI.
 * \param _port Server port.
 */
HTTP::HTTP(string _server, unsigned int _port) {
	server = _server;
	port = _port;

	HTTP::raw_response = "";
}

/**
 * Adds a header to the header list.
 *
 * \param name Header name.
 * \param value Header value.
 */
void HTTP::add_header(string name, string value) {
	vector<string> header;
	header.push_back(name);
	header.push_back(value);

	headers.push_back(header);
}

/**
 * Request something from a server.
 *
 * \param location The location of something in a server.
 * \return HTTP_Response instance.
 */
HTTP_Response HTTP::request(string type, string location, string body) {
	HTTP_Response response;

	// Setup the socket and connect.
	Socket socket(server, port, &socket_data_callback);
	socket.connect();

	// Just a normal HTTP request.
	socket.send_data(type + " " + location + " HTTP/1.1\r\n");
	socket.send_data("Host: " + server + "\r\n");

	for (size_t i = 0; i < headers.size(); i++) {
		socket.send_data(headers.at(i).at(0) + ": " + headers.at(i).at(1) + "\r\n");
	}

	
	if (body.empty()) {
		socket.send_data("\r\n");
	} else {
		stringstream stream;
		stream << "Content-Length: " << body.length() << "\r\n\r\n";

		socket.send_data(stream.str());
		socket.send_data(body);
		socket.send_data("\r\n\r\n");
	}

	socket.receive();

	// Populate the HTTP_Response object.
	response.raw = HTTP::raw_response;
	response.status_code = atoi(HTTP::raw_response.substr(HTTP::raw_response.find(" ") + 1, 3).c_str());
	response.headers = parse_headers();
	response.body = HTTP::raw_response.substr(HTTP::raw_response.find("\r\n\r\n") + 4);

	response.status_message = HTTP::raw_response.substr(HTTP::raw_response.find(" ") + 5);
	response.status_message = response.status_message.substr(0, response.status_message.find("\r\n"));

	return response;
}

/**
 * Socket callback handler.
 *
 * \param data Data from a socket connection.
 * \return True if everything went right.
 */
bool HTTP::socket_data_callback(string data) {
	raw_response += data;
	return true;
}

/**
 * Parse HTTP headers.
 *
 * \return Vector of string vectors (name, value).
 */
vector<vector<string> > HTTP::parse_headers() {
	string str_headers = HTTP::raw_response.substr(HTTP::raw_response.find("\r\n") + 2);
	str_headers = str_headers.substr(0, HTTP::raw_response.find("\r\n\r\n"));
	vector<vector<string> > response_headers;

	while (str_headers.find("\r\n") != string::npos) {
		string curr_header = str_headers.substr(0, str_headers.find("\r\n"));

		// Just making sure...
		if (curr_header != "\r\n" && curr_header.find(": ") != string::npos) {
			string name = curr_header.substr(0, curr_header.find(": "));
			string value = curr_header.substr(curr_header.find(": ") + 2);

			vector<string> header;
			header.push_back(name);
			header.push_back(value);

			response_headers.push_back(header);
		}

		// Remove the used header.
		str_headers = str_headers.substr(str_headers.find("\r\n") + 2);
	}

	return response_headers;
}
