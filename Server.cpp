/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:17:16 by hmeftah           #+#    #+#             */
/*   Updated: 2023/09/27 13:44:14 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Toolkit.hpp"
#include "Auth.hpp"


/* === Coplien's form ===*/
Server::Server() : client_count(0)
{
	_bzero(&this->hints, sizeof(this->hints));
	this->server_socket_fd = -1;
	this->socket_data_size = sizeof(this->client_sock_data);
	this->clients.clear();
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

Server::Server(std::string port, std::string pass) {
	Server();
	CreateServer(port, pass);
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
	int optval = 1;
	if (this->GenerateServerData(port))
		return 1;
	
	this->password = pass;
	this->server_socket_fd = socket(this->hints.ai_family, this->hints.ai_socktype, this->hints.ai_protocol);
	if (this->server_socket_fd == -1) {
		std::cerr << "Error: Socket creation has failed!" << std::endl;
		return 1;
	}
	setsockopt(server_socket_fd, SOL_SOCKET, SO_REUSEADDR,  &optval, sizeof(optval));
	if (bind(this->server_socket_fd, this->res->ai_addr, this->res->ai_addrlen) == -1) {
		std::cerr << "Error: Couldn't bind the socket to host address!" << std::endl;
		return 1;
	}
	if (listen(this->server_socket_fd, MAX_IRC_CONNECTIONS) == -1) {
		std::cerr << "Cannot listen to port: " << port << std::endl;
		return 1;
	}
	std::cout << "Server has been successfully created for port " + port << std::endl;
	fcntl(server_socket_fd, F_SETFL, O_NONBLOCK);
	InsertSocketFileDescriptorToPollQueue(server_socket_fd);
	OnServerLoop();
	return 0;
}

void	Server::InsertSocketFileDescriptorToPollQueue(const int connection_fd) {

	struct pollfd tmp;

	tmp.fd = connection_fd;
	tmp.events = POLLIN | POLLOUT;
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
	std::vector<struct pollfd>::iterator it = this->c_fd_queue.begin();
	std::vector<Client>::iterator itx = this->clients.begin();

	c_fd_queue.erase(std::remove_if(c_fd_queue.begin(), c_fd_queue.end(), [client_fd](const struct pollfd& element) { return element.fd == client_fd; }), 
    c_fd_queue.end());

	while (itx != clients.end()) {
		if (itx->getSockID() == client_fd) {
			clients.erase(itx);
			break ;
		}
		itx++;
	}
}

void	Server::PreformServerCleanup(void) {
	freeaddrinfo(this->res);
}

void	Server::DeleteClient(int client_fd) {
	std::vector<int>::iterator it = client_fds.begin();

	it = std::find(it, client_fds.end(), client_fd);
	close(client_fd);
	PopOutClientFd(client_fd);
	if (it != client_fds.end())
		this->client_fds.erase(it);
	this->client_count--;
}

void	Server::InsertClient(int client_fd) {
		Client User(client_fd, 1);

		this->clients.push_back(User);
		InsertSocketFileDescriptorToPollQueue(client_fd);
		send(client_fd, INTRO, _strlen(INTRO), 0);
		this->client_fds.push_back(client_fd);
		this->client_count++;
}

int	Server::FindClient(int client_fd) {
	for (size_t i = 0; i < clients.size(); i++) {
		if (client_fd == clients[i].getSockID())
			return ((int)i);
	}
	return -1;
}

void	Server::ReadClientFd(int client_fd) {
	char	buf[MAX_IRC_MSGLEN];

	_bzero(buf, MAX_IRC_MSGLEN);
	int rb = recv(client_fd, buf, MAX_IRC_MSGLEN, MSG_PEEK);
	if (rb > 0) {
		while (SRH)
		{
			rb = recv(client_fd, buf, MAX_IRC_MSGLEN, 0);
			if (rb <= 0) {
				break ;
			} else {
				buf[rb] = 0;
				this->raw_data += buf;
			}
		}
		std::cout << buf << std::endl;
	}
}

bool	Server::JustConnected(int socketfd) {
	size_t i = 0;

	if (!this->clients.empty()) {
		while (i < this->clients.size()) {
			if (socketfd == clients[i].getSockID()) {
				return clients[i].JustConnectedStatus();
			}
			i++;
		}
	}
	return 0;
}

void	Server::OnServerFdQueue(void) {
	for (size_t i = 1, found = 0; i < this->client_count + 1; i++) {
		if (this->c_fd_queue[i].revents & POLLIN) {
			ReadClientFd(this->c_fd_queue[i].fd);
			if (JustConnected(c_fd_queue[i].fd)) {
				if (Auth::Authenticate(raw_data, password)) {
					found = FindClient(this->c_fd_queue[i].fd);
				}
			}
		
		}
		else if (this->c_fd_queue[i].revents & POLLOUT) {
			if (found >= 0 && clients[found].getSockID() == c_fd_queue[i].fd)
				send(c_fd_queue[i].fd, DIE, sizeof(DIE) - 1, 0);
				DeleteClient(c_fd_queue[i].fd);
		}
		if (this->c_fd_queue[i].revents == (POLLIN | POLLHUP)) {
			std::cout << "Client has disconnected, IP: " << inet_ntoa(this->client_sock_data.sin_addr) << std::endl;
			DeleteClient(c_fd_queue[i].fd);	
		}
	}
}

void	Server::OnServerLoop(void) {
	while (SRH) {
	int 	new_client_fd = -1;
	int 	poll_num = poll(&this->c_fd_queue[0], this->client_count + 1, 0);
	
	new_client_fd = accept(this->server_socket_fd, (struct sockaddr *)&this->client_sock_data, &this->socket_data_size);
	if (new_client_fd > 0) {
		fcntl(new_client_fd, F_SETFL, O_NONBLOCK);
		std::cout << "Connected IP: " << inet_ntoa(this->client_sock_data.sin_addr) << std::endl;
		InsertClient(new_client_fd);
		std::cout << "Total Clients: " << clients.size() << std::endl;
	}
	if (poll_num > 0)
		OnServerFdQueue();
	}
}	