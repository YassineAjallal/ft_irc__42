/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:17:16 by hmeftah           #+#    #+#             */
/*   Updated: 2023/09/24 21:04:44 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Toolkit.hpp"

/* === Coplien's form ===*/
Server::Server() : client_count(0)
{
	_bzero(&this->hints, sizeof(this->hints));
	this->server_socket_fd = -1;
	this->socket_data_size = sizeof(this->client_sock_data);
}

Server::Server(const Server& copy)
{
	(void) copy;
	_memset(&this->hints, (char *)&copy.hints, sizeof(copy.hints));
	this->server_socket_fd = copy.server_socket_fd;
	this->c_fd_queue = copy.c_fd_queue;
	this->client_fds = copy.client_fds;
	this->client_count = copy.client_count;
}

Server &Server::operator=(const Server& copy)
{
	if (this != &copy) {
		_memset(&this->hints, (char *)&copy.hints, sizeof(copy.hints));
		this->server_socket_fd = copy.server_socket_fd;
		this->c_fd_queue = copy.c_fd_queue;
		this->client_fds = copy.client_fds;
		this->client_count = copy.client_count;
	}
	return (*this);
}

Server::~Server() {}

/* === Member Functions ===*/

bool	Server::GenerateServerData(const std::string &port) {
	this->hints.ai_family = AF_INET;
	this->hints.ai_socktype = SOCK_STREAM;
	this->hints.ai_flags = AI_PASSIVE;
	if (getaddrinfo(NULL, port.c_str(), &this->hints, &this->res)) {
		std::cerr << "Error: Couldn't acquire address info!" << std::endl;
		return 1;
	}
	return 0;
}

bool	Server::CreateServer(const std::string &port, const std::string &pass) {
	if (this->GenerateServerData(port))
		return 1;
	
	this->password = pass;
	this->server_socket_fd = socket(this->hints.ai_family, this->hints.ai_socktype, this->hints.ai_protocol);
	if (this->server_socket_fd == -1) {
		std::cerr << "Error: Socket creation has failed!" << std::endl;
		return 1;
	}
	if (bind(this->server_socket_fd, this->res->ai_addr, this->res->ai_addrlen) == -1) {
		std::cerr << "Error: Couldn't bind the socket to host address!" << std::endl;
		return 1;
	}
	if (listen(this->server_socket_fd, MAX_IRC_CONNECTIONS) == -1) {
		std::cerr << "Cannot listen to port: " << port << std::endl;
		return 1;
	}
	std::cout << "Server has been successfully created for port " + port << std::endl;
	this->OnServerLoop();
	return 0;
}

void	Server::InsertSocketFileDescriptorToPollQueue(const int connection_fd) {

	struct pollfd tmp;

	tmp.fd = connection_fd;
	tmp.events = POLLIN | POLLOUT;
	this->c_fd_queue.push_back(tmp);
	this->c_fd_queue.push_back(tmp);
}

void	 Server::CloseConnections(void) {
	for (size_t i = 0; i < this->client_fds.size(); i++) {
		if (this->client_fds.at(i) > 2)
			close(this->client_fds.at(i));
	}
	if (this->server_socket_fd > 2) {
		close(this->server_socket_fd);
	}
	PreformServerCleanup();
}

void	Server::PopOutClientFd(int client_fd) {
	for (size_t i = 0; i < this->c_fd_queue.size(); i++) {
		if (this->c_fd_queue[i].fd == client_fd) {
			this->c_fd_queue[i].fd = -1;
			return ;
		}
	}
}

void	Server::PreformServerCleanup(void) {
	freeaddrinfo(this->res);
}

std::string	Server::OnServerFdQueue(void) {
	char buf[MAX_IRC_MSGLEN];

	_bzero(buf, sizeof(buf));
	for (size_t i = 0; i < this->client_count; i++)
		if (this->c_fd_queue[i].fd
			&& (this->c_fd_queue[i].revents & POLLIN)) {
			recv(c_fd_queue[i].fd, buf, MAX_IRC_MSGLEN, 0);
			send(c_fd_queue[i].fd, INTRO, sizeof(INTRO) - 1, 0);
	}
	std::cout << "[" << buf << "]" << std::endl;
	return (buf);
}

void	Server::OnServerLoop(void) {
	int new_client_fd = -1;
	std::string holder;
	
	while (SRH) {
		new_client_fd = accept(this->server_socket_fd, (struct sockaddr *)&this->client_sock_data, &this->socket_data_size);
		if (new_client_fd == -1)
			std::cerr << "Connection has been aborted due to an error!" << std::endl;
		else {
			this->client_fds.push_back(new_client_fd);
			this->client_count++;
		}
		std::cout << "Connected IP: " << inet_ntoa(this->client_sock_data.sin_addr) << std::endl;
		InsertSocketFileDescriptorToPollQueue(new_client_fd);
	
		int ret = poll(&this->c_fd_queue[0], client_count, 0);
		if (ret < 0) {
			std::cerr << "Unexpected Error in poll, closing connections..." << std::endl;
			CloseConnections();
			return ;
		} else if (ret > 0) {
			holder = OnServerFdQueue();
		}
	}
}