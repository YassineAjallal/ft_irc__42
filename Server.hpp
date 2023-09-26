/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 15:09:17 by hmeftah           #+#    #+#             */
/*   Updated: 2023/09/26 16:27:57 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <iterator>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <iostream>
#include <string>
#include <map>
#include <ctime>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/poll.h>
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
#include "Toolkit.hpp"
#include "Auth.hpp"
#include "Client.hpp"

#define INTRO "Welcome to:\n" "	██████  ▄▄▄       ██▀███   ▄▄▄       ██░ ██     ██▓ ██▀███   ▄████▄       ██████ ▓█████  ██▀███   ██▒   █▓▓█████  ██▀███	\n" "▒██    ▒ ▒████▄    ▓██ ▒ ██▒▒████▄    ▓██░ ██▒   ▓██▒▓██ ▒ ██▒▒██▀ ▀█     ▒██    ▒ ▓█   ▀ ▓██ ▒ ██▒▓██░   █▒▓█   ▀ ▓██ ▒ ██▒ \n" "░ ▓██▄   ▒██  ▀█▄  ▓██ ░▄█ ▒▒██  ▀█▄  ▒██▀▀██░   ▒██▒▓██ ░▄█ ▒▒▓█    ▄    ░ ▓██▄   ▒███   ▓██ ░▄█ ▒ ▓██  █▒░▒███   ▓██ ░▄█ ▒ \n" "  ▒   ██▒░██▄▄▄▄██ ▒██▀▀█▄  ░██▄▄▄▄██ ░▓█ ░██    ░██░▒██▀▀█▄  ▒▓▓▄ ▄██▒     ▒   ██▒▒▓█  ▄ ▒██▀▀█▄    ▒██ █░░▒▓█  ▄ ▒██▀▀█▄   \n" "▒██████▒▒ ▓█   ▓██▒░██▓ ▒██▒ ▓█   ▓██▒░▓█▒░██▓   ░██░░██▓ ▒██▒▒ ▓███▀ ░   ▒██████▒▒░▒████▒░██▓ ▒██▒   ▒▀█░  ░▒████▒░██▓ ▒██▒ \n" "▒ ▒▓▒ ▒ ░ ▒▒   ▓▒█░░ ▒▓ ░▒▓░ ▒▒   ▓▒█░ ▒ ░░▒░▒   ░▓  ░ ▒▓ ░▒▓░░ ░▒ ▒  ░   ▒ ▒▓▒ ▒ ░░░ ▒░ ░░ ▒▓ ░▒▓░   ░ ▐░  ░░ ▒░ ░░ ▒▓ ░▒▓░ \n" "░ ░▒  ░ ░  ▒   ▒▒ ░  ░▒ ░ ▒░  ▒   ▒▒ ░ ▒ ░▒░ ░    ▒ ░  ░▒ ░ ▒░  ░  ▒      ░ ░▒  ░ ░ ░ ░  ░  ░▒ ░ ▒░   ░ ░░   ░ ░  ░  ░▒ ░ ▒░ \n" "░  ░  ░    ░   ▒     ░░   ░   ░   ▒    ░  ░░ ░    ▒ ░  ░░   ░ ░           ░  ░  ░     ░     ░░   ░      ░░     ░     ░░   ░  \n" "      ░        ░  ░   ░           ░  ░ ░  ░  ░    ░     ░     ░ ░               ░     ░  ░   ░           ░     ░  ░   ░      \n" "                                                              ░                                         ░                   \r\n"
#define MAX_IRC_CONNECTIONS 75
#define MAX_SAME_CLIENT_CONNECTIONS 4
#define MAX_IRC_MSGLEN 4096
#define SRH 1

struct AddressData {
	protected:
		struct 	addrinfo	hints, *res;
		struct 	sockaddr_in	client_sock_data;
		socklen_t 			socket_data_size;
		int 				server_socket_fd;
};

class Server : public AddressData
{
	public:
		Server();
		Server(const Server& copy);
		Server(std::string port, std::string pass);
		Server &operator=(const Server& copy);
		~Server();

		bool	CreateServer(const std::string &port, const std::string &pass);

	private:
		size_t		client_count;
		std::string password;
		std::string raw_data;
		std::vector<Client> clients;
		std::vector<struct pollfd> c_fd_queue;
		std::vector<int> client_fds;
		void		OnServerLoop();
		void		CloseConnections();
		bool		JustConnected(int socketfd);
		void		OnServerFdQueue(void);
		void		PreformServerCleanup();
		void		InsertClient(int client_fd);
		void		DeleteClient(int client_fd);
		void		ReadClientFd(int client_fd);
		void		PopOutClientFd(int client_fd);
		bool		GenerateServerData(const std::string &port);
		void		InsertSocketFileDescriptorToPollQueue(const int connection_fd);
};
