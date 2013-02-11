/**
 *  sockets.cpp
 *  Raw internet sockets.
 *
 *  Nathan Campos <nathanpc@dreamintech.net>
 */

#ifndef LIBINET_SOCKETS_H_
#define LIBINET_SOCKETS_H_

#include <string>

typedef bool (*HandlerCallback)(std::string);

class Socket {
	private:
		int socket_descriptor;
		bool connected;
		pthread_t thread;
		HandlerCallback handler_callback;

		static void *handle_recv_thread_helper(void *context);

	public:
		Socket(std::string server, unsigned int port, HandlerCallback _handler_callback);

		void *handle_recv();
		int send_data(std::string data);
		void close_connection();
};

#endif
