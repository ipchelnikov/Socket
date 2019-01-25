#include "receive_socket.hpp"
#include "send_socket.hpp"

#include <iostream>
#include <thread>

#include <ws2tcpip.h>

int recvFunction() {
	/*
	ReceiveSocket myRecvSocket(std::string("127.0.0.1"), 1111);
	
	while (auto data = myRecvSocket.receive()) {
		std::cout << std::string(data->first, data->second) << std::endl;
	}
	*/

	int iResult = 0;

	WSADATA wsaData;

	SOCKET RecvSocket;
	sockaddr_in RecvAddr;

	unsigned short Port = 27015;

	char RecvBuf[1024];
	int BufLen = 1024;

	sockaddr_in SenderAddr;
	int SenderAddrSize = sizeof(SenderAddr);

	//-----------------------------------------------
	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR) {
		wprintf(L"WSAStartup failed with error %d\n", iResult);
		return 1;
	}
	//-----------------------------------------------
	// Create a receiver socket to receive datagrams
	RecvSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (RecvSocket == INVALID_SOCKET) {
		wprintf(L"socket failed with error %d\n", WSAGetLastError());
		return 1;
	}
	//-----------------------------------------------
	// Bind the socket to any address and the specified port.
	RecvAddr.sin_family = AF_INET;
	RecvAddr.sin_port = htons(Port);
	RecvAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	iResult = bind(RecvSocket, (SOCKADDR *)& RecvAddr, sizeof(RecvAddr));
	if (iResult != 0) {
		wprintf(L"bind failed with error %d\n", WSAGetLastError());
		return 1;
	}
	//-----------------------------------------------
	// Call the recvfrom function to receive datagrams
	// on the bound socket.
	wprintf(L"Receiving datagrams...\n");
	iResult = recvfrom(RecvSocket,
		RecvBuf, BufLen, 0, (SOCKADDR *)& SenderAddr, &SenderAddrSize);
	if (iResult == SOCKET_ERROR) {
		wprintf(L"recvfrom failed with error %d\n", WSAGetLastError());
	}

	//-----------------------------------------------
	// Close the socket when finished receiving datagrams
	wprintf(L"Finished receiving. Closing socket.\n");

	std::cout << std::string(RecvBuf, iResult) << std::endl;

	iResult = closesocket(RecvSocket);
	if (iResult == SOCKET_ERROR) {
		wprintf(L"closesocket failed with error %d\n", WSAGetLastError());
		return 1;
	}

	//-----------------------------------------------
	// Clean up and exit.
	wprintf(L"Exiting.\n");
	WSACleanup();
	return 0;
}

int main(int argc, char* argv[]) {

	std::cout << "socket test start" << std::endl;
	/*
	SendSocket mySendSocket(std::string("127.0.0.1"), 1112, std::string("127.0.0.1"), 1111);

	std::string myMessage = "Hello message";

	mySocket.send(myMessage.c_str(), myMessage.length());


	std::getchar();
	*/

	std::thread recv_thread(recvFunction);
	recv_thread.detach();

	std::this_thread::sleep_for(std::chrono::microseconds(500));

	int iResult;
	WSADATA wsaData;

	SOCKET SendSocket = INVALID_SOCKET;
	sockaddr_in RecvAddr;

	unsigned short Port = 27015;

	char SendBuf[1024];
	int BufLen = 1024;

	//----------------------
	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR) {
		wprintf(L"WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	//---------------------------------------------
	// Create a socket for sending data
	SendSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (SendSocket == INVALID_SOCKET) {
		wprintf(L"socket failed with error: %ld\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}
	//---------------------------------------------
	// Set up the RecvAddr structure with the IP address of
	// the receiver (in this example case "192.168.1.1")
	// and the specified port number.
	RecvAddr.sin_family = AF_INET;
	RecvAddr.sin_port = htons(Port);
	InetPton(AF_INET, "127.0.0.1", &RecvAddr.sin_addr.s_addr);

	//---------------------------------------------
	// Send a datagram to the receiver
	wprintf(L"Sending a datagram to the receiver...\n");

	std::string string_to_send = "Hello socket!";

	//iResult = sendto(SendSocket,
	//	SendBuf, BufLen, 0, (SOCKADDR *)& RecvAddr, sizeof(RecvAddr));

	iResult = sendto(SendSocket,
		string_to_send.c_str(), string_to_send.length(), 0, (SOCKADDR *)& RecvAddr, sizeof(RecvAddr));

	if (iResult == SOCKET_ERROR) {
		wprintf(L"sendto failed with error: %d\n", WSAGetLastError());
		closesocket(SendSocket);
		WSACleanup();
		return 1;
	}
	//---------------------------------------------
	// When the application is finished sending, close the socket.
	wprintf(L"Finished sending. Closing socket.\n");
	iResult = closesocket(SendSocket);
	if (iResult == SOCKET_ERROR) {
		wprintf(L"closesocket failed with error: %d\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}
	//---------------------------------------------
	// Clean up and quit.
	wprintf(L"Exiting.\n");
	WSACleanup();
	
	getchar();
	return 0;
}