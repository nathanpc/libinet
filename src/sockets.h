/**
 *  sockets.cpp
 *  Raw internet sockets.
 *
 *  Nathan Campos <nathanpc@dreamintech.net>
 */

#ifndef LIBINET_SOCKETS_H_
#define LIBINET_SOCKETS_H_

#include <string>

class Socket {
	private:
		int socket_descriptor;
		bool connected;

	public:
		Socket(std::string server, std::string port);

		int send_data(std::string data);
		void close_connection();
};

#endif
