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

    public:
        Socket(std::string server, std::string port);
};

#endif
