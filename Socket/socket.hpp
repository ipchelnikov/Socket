#ifndef SOCKET_SOCKET_HPP
#define SOCKET_SOCKET_HPP

#include <Winsock2.h>

#include <string>

class Socket {
protected:
	Socket(const std::string &addr, int8_t port);
	virtual ~Socket();
	static int startupSocket();

	SOCKET sock;
};

#endif // !SOCKET_HPP