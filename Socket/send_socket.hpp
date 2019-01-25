#ifndef SOCKET_SEND_SOCKET_HPP
#define SOCKET_SEND_SOCKET_HPP

#include "Socket.hpp"

class SendSocket : public Socket {
public:
	SendSocket(const std::string &&addr, int8_t port);
};

#endif // !SOCKET_RECEIVE_SOCKET_HPP#pragma once
