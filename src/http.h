/**
 *  http.h
 *  HTTP client for human C++ developers.
 *
 *  Nathan Campos <nathanpc@dreamintech.net>
 */

#ifndef LIBINET_HTTP_H_
#define LIBINET_HTTP_H_

#include <string>
#include <vector>

#include "sockets.h"

class HTTP_Response {
	public:
		std::string raw;
		std::vector<std::vector<std::string> > headers;
		std::string body;

		HTTP_Response();
};

class HTTP {
	private:
		Socket socket;

		static std::string raw_response;
		static bool socket_data_callback(std::string data);

	public:
		std::string server;
		unsigned int port;
		std::vector<std::vector<std::string> > headers;

		HTTP();
		HTTP(std::string _server, unsigned int _port);

		void add_header(std::string name, std::string value);
		HTTP_Response request(std::string location);
};

#endif

