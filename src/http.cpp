/**
 *  http.cpp
 *  HTTP client for human C++ developers.
 *
 *  Nathan Campos <nathanpc@dreamintech.net>
 */

#include <iostream>
#include <string>
#include <vector>

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
HTTP_Response HTTP::request(string location) {
	HTTP_Response response;

	// Setup the socket and connect.
	Socket socket(server, port, &socket_data_callback);
	socket.connect();

	// Just a normal HTTP request.
	socket.send_data("GET " + location + " HTTP/1.1\r\n");
	socket.send_data("Host: " + server + "\r\n");

	for (size_t i = 0; i < headers.size(); i++) {
		socket.send_data(headers.at(i).at(0) + ": " + headers.at(i).at(1) + "\r\n");
	}

	socket.send_data("\r\n");
	socket.receive();

	// Populate the HTTP_Response object.
	response.raw = HTTP::raw_response;

	return response;
}
