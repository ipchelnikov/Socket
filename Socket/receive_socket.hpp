#ifndef SOCKET_RECEIVE_SOCKET_HPP
#define SOCKET_RECEIVE_SOCKET_HPP

#include "Socket.hpp"

#include <optional>

class ReceiveSocket : public Socket {
public:
	ReceiveSocket(const std::string &addr, int8_t port) : Socket(addr, port) {}
	ReceiveSocket(std::string &&addr, int8_t port) : Socket(addr, port) {}
	std::optional<std::pair<char*, int>> receive() const;
};

#endif // !SOCKET_RECEIVE_SOCKET_HPP