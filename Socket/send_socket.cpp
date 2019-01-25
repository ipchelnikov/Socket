#include "send_socket.hpp"

SendSocket::SendSocket(const std::string &&addr, int8_t port) : Socket(addr, port) 
{
	/*
	auto err = connect(sock, ptr->ai_addr, (int)ptr->ai_addrlen);

	if (err == SOCKET_ERROR) {
		closesocket(sock);
		sock = INVALID_SOCKET;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		WSACleanup();
		return 1;
	}
	*/
}