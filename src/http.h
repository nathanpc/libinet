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
#include "uri.h"

typedef void (*ProgressCallback)(size_t, size_t);

class HTTP_Response {
	public:
		std::string raw;
		unsigned int status_code;
		std::string status_message;

		std::vector<std::vector<std::string> > headers;
		std::string body;

		HTTP_Response();
};

class HTTP {
	private:
		Socket socket;

		static std::string raw_response;
		static size_t content_length;
		static size_t received_body_length;

		static ProgressCallback progress_callback;
		static bool progress_callback_set;

		static bool socket_data_callback(std::string data);

	public:
		std::string server;
		unsigned int port;
		std::string location;
		std::vector<std::vector<std::string> > headers;

		HTTP();
		HTTP(std::string _server, unsigned int _port, std::string _location);
		HTTP(URI uri);

		void add_header(std::string name, std::string value);
		std::vector<std::vector<std::string> > parse_headers();

		void set_progress_callback(ProgressCallback callback);

		HTTP_Response request(std::string type, std::string body = "");
};

#endif

