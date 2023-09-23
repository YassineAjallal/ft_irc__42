#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <iostream>
#include <string>
#include "cerrno"

/*
	Ports under 1024 are reserved.
	Don't go over 65535 port number
*/

void	_bzero(void *ptr, size_t size) {

	if (ptr) {
		for (size_t i = 0; i < size; i++) {
			*((char *)ptr + i) = 0;
		}
	}
}

void	init_socket_data(struct addrinfo *socket_data) {
	socket_data->ai_family = AF_INET;
	socket_data->ai_socktype = SOCK_STREAM;
	socket_data->ai_flags = AI_PASSIVE;
}

int main(int ac, char **av) {
	if (ac == 3) {
		struct addrinfo hints, *res;
		struct sockaddr socket_data;
		int socket_fd, connection_fd;
		socklen_t socket_data_size;

		_bzero(&hints, sizeof(hints));
		init_socket_data(&hints);
		if (getaddrinfo(NULL, av[1], &hints, &res)) {
			std::cerr << "Error: Couldn't acquire address info!" << std::endl;
			return 1;
		}
		socket_fd = socket(hints.ai_family, hints.ai_socktype, hints.ai_protocol);
		if (socket_fd == -1) {
			std::cout << strerror(errno) << std::endl;
			std::cerr << "Error: Socket creation has failed!" << std::endl;
			return 1;
		}
		if (bind(socket_fd, res->ai_addr, res->ai_addrlen) == -1) {
			std::cerr << "Error: Couldn't bind the socket to host address!" << std::endl;
			return 1;
		}
		if (listen(socket_fd, 25) == -1) {
			std::cerr << "Cannot listen to port: " << av[1] << std::endl;
			return 1;
		}
		socket_data_size = sizeof(socket_data);
		connection_fd = accept(socket_fd, &socket_data, &socket_data_size);
		if (connection_fd == -1) {
			std::cerr << "Connection has been aborted due to an error!" << std::endl;
			return 1;
		}
		while (1) {}
	}
	else {
		std::cerr << "GUIDE: ./ircserv port password" << std::endl;
		return 2;
	}
	return 0;
}