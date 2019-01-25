#include "socket.hpp"

#include <ws2tcpip.h>

// link with Ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

#include <iostream>

Socket::Socket(const std::string &addr, int8_t port) {

	startupSocket();

	struct addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = IPPROTO_UDP;

	struct addrinfo *result = NULL;


	auto dwRetval = getaddrinfo(addr.c_str(), "11111", &hints, &result);

	if (dwRetval != 0) {

	}

	sock = INVALID_SOCKET;
	sock = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

	if (sock == INVALID_SOCKET) {
		printf("Error at socket(): %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
	}
}

Socket::~Socket() {
	closesocket(sock);
	WSACleanup();
}

int Socket::startupSocket() {

	WORD wVersionRequested;
	WSADATA wsaData;

	// Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h
	wVersionRequested = MAKEWORD(2, 2);

	int err = WSAStartup(wVersionRequested, &wsaData);

	// Confirm that the WinSock DLL supports 2.2.
	// Note that if the DLL supports versions greater
	// than 2.2 in addition to 2.2, it will still return
	// 2.2 in wVersion since that is the version we
	// requested.

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		/* Tell the user that we could not find a usable */
		/* WinSock DLL.                                  */
		printf("Could not find a usable version of Winsock.dll\n");
		WSACleanup();
		return 1;
	}
	
	std::cout << "The Winsock 2.2 dll was found okay\n" << std::endl;

}


