/**
 *  uri.h
 *  URI parsing helper class.
 *
 *  \author Nathan Campos <nathanpc@dreamintech.net>
 */

#ifndef LIBINET_URI_H_
#define LIBINET_URI_H_

#include <string>
#include <vector>

class URI {
	private:
		void parse();

		void parse_port(std::string _server);
		void parse_params(std::string _params);

		void parse_param(std::string str_param);

	public:
		std::string uri;

		std::string protocol;
		std::string server;
		unsigned int port;

		std::string location;
		std::vector<std::vector<std::string> > params;

		// Constructors
		URI();
		URI(std::string _uri);

		void parse(std::string _uri);
		std::string get_full_location();
};

#endif
