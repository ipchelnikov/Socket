#include "receive_socket.hpp"

std::optional<std::pair<char*, int>> ReceiveSocket::receive() const {

	std::pair<char*, int> result;

	auto err = recv(sock, result.first, result.second, 0);

	return err > 0 ? std::optional<std::pair<char*, int>>{result} : std::nullopt;
}