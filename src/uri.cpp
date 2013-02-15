/**
 *  uri.cpp
 *  URI parsing helper class.
 *
 *  \author Nathan Campos <nathanpc@dreamintech.net>
 */

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

#include "uri.h"
using namespace std;


URI::URI() {
	uri = "";
}

URI::URI(string _uri) {
	uri = _uri;
	parse();
}

void URI::parse(string _uri) {
	uri = _uri;
	parse();
}

void URI::parse() {
	string tmp_uri = string(uri);

	// Parse the protocol
	if (tmp_uri.find("://") != string::npos) {
		protocol = tmp_uri.substr(0, tmp_uri.find("://"));
		tmp_uri = tmp_uri.substr(tmp_uri.find("://") + 3);
	}

	// Parse the server (and port), and location string, and parameters.
	if (tmp_uri.find("/") != string::npos) {
		string tmp_server = tmp_uri.substr(0, tmp_uri.find("/"));

		parse_port(tmp_server);
		server = tmp_server;
		tmp_uri = tmp_uri.substr(tmp_uri.find("/") + 1);

		// Check if it has a location.
		if (!tmp_uri.empty()) {
			// Check for parameters.
			if (tmp_uri.find("?") != string::npos) {
				location = tmp_uri.substr(0, tmp_uri.find("?"));
				tmp_uri = tmp_uri.substr(tmp_uri.find("?") + 1);

				parse_params(tmp_uri);
			} else {
				location = tmp_uri;
			}

			tmp_uri = "";
		}
	} else {
		parse_port(tmp_uri);
		server = tmp_uri;
		location = "/";

		tmp_uri = "";
	}
}

void URI::parse_port(string _server) {
	if (_server.find(":") != string::npos) {
		port = atoi(_server.substr(_server.find(":") - 1).c_str());
		_server = _server.substr(0, _server.find(":"));
	} else {
		// TODO: Get default port according to the protocol.
		port = 80;
	}
}

void URI::parse_params(string _params) {
	while (_params.find("&") != string::npos) {
		string str_param = _params.substr(0, _params.find("&"));
		parse_param(str_param);

		_params = _params.substr(_params.find("&") + 1);
	}

	parse_param(_params);
}

void URI::parse_param(string str_param) {
	vector<string> param;

	param.push_back(str_param.substr(0, str_param.find("=")));
	param.push_back(str_param.substr(str_param.find("=") + 1));
	params.push_back(param);
}

string URI::get_full_location() {
	stringstream full_location;
	full_location << location;

	for (size_t i = 0; i < params.size(); i++) {
		if (i == 0) {
			full_location << "?";
		}

		full_location << params[i][0] << "=" << params[i][1] << "&";
	}

	if (params.size() > 0) {
		string str_full = full_location.str();
		return str_full.substr(0, str_full.length() - 1);
	}

	return full_location.str();
}
