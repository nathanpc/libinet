/**
 *  sockets.h
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

		std::string server;
		unsigned int port;

		static void *handle_recv_thread_helper(void *context);

	public:
		// Constructors
		Socket();
		Socket(std::string _server, unsigned int _port, HandlerCallback _handler_callback);

		// Connectors?
		void connect();
		void connect(std::string server, unsigned int port, HandlerCallback _handler_callback);

		void *receive();
		int send_data(std::string data);
		void close_connection();
};

#endif
