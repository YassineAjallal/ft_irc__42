/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 15:09:17 by hmeftah           #+#    #+#             */
/*   Updated: 2023/09/24 21:02:29 by hmeftah          ###   ########.fr       */
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
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/poll.h>
#include <fcntl.h>
#include <unistd.h>
#include "Toolkit.hpp"
#include "Auth.hpp"

#define INTRO "Welcome to:\n" "	██████  ▄▄▄       ██▀███   ▄▄▄       ██░ ██     ██▓ ██▀███   ▄████▄       ██████ ▓█████  ██▀███   ██▒   █▓▓█████  ██▀███	\n" "▒██    ▒ ▒████▄    ▓██ ▒ ██▒▒████▄    ▓██░ ██▒   ▓██▒▓██ ▒ ██▒▒██▀ ▀█     ▒██    ▒ ▓█   ▀ ▓██ ▒ ██▒▓██░   █▒▓█   ▀ ▓██ ▒ ██▒ \n" "░ ▓██▄   ▒██  ▀█▄  ▓██ ░▄█ ▒▒██  ▀█▄  ▒██▀▀██░   ▒██▒▓██ ░▄█ ▒▒▓█    ▄    ░ ▓██▄   ▒███   ▓██ ░▄█ ▒ ▓██  █▒░▒███   ▓██ ░▄█ ▒ \n" "  ▒   ██▒░██▄▄▄▄██ ▒██▀▀█▄  ░██▄▄▄▄██ ░▓█ ░██    ░██░▒██▀▀█▄  ▒▓▓▄ ▄██▒     ▒   ██▒▒▓█  ▄ ▒██▀▀█▄    ▒██ █░░▒▓█  ▄ ▒██▀▀█▄   \n" "▒██████▒▒ ▓█   ▓██▒░██▓ ▒██▒ ▓█   ▓██▒░▓█▒░██▓   ░██░░██▓ ▒██▒▒ ▓███▀ ░   ▒██████▒▒░▒████▒░██▓ ▒██▒   ▒▀█░  ░▒████▒░██▓ ▒██▒ \n" "▒ ▒▓▒ ▒ ░ ▒▒   ▓▒█░░ ▒▓ ░▒▓░ ▒▒   ▓▒█░ ▒ ░░▒░▒   ░▓  ░ ▒▓ ░▒▓░░ ░▒ ▒  ░   ▒ ▒▓▒ ▒ ░░░ ▒░ ░░ ▒▓ ░▒▓░   ░ ▐░  ░░ ▒░ ░░ ▒▓ ░▒▓░ \n" "░ ░▒  ░ ░  ▒   ▒▒ ░  ░▒ ░ ▒░  ▒   ▒▒ ░ ▒ ░▒░ ░    ▒ ░  ░▒ ░ ▒░  ░  ▒      ░ ░▒  ░ ░ ░ ░  ░  ░▒ ░ ▒░   ░ ░░   ░ ░  ░  ░▒ ░ ▒░ \n" "░  ░  ░    ░   ▒     ░░   ░   ░   ▒    ░  ░░ ░    ▒ ░  ░░   ░ ░           ░  ░  ░     ░     ░░   ░      ░░     ░     ░░   ░  \n" "      ░        ░  ░   ░           ░  ░ ░  ░  ░    ░     ░     ░ ░               ░     ░  ░   ░           ░     ░  ░   ░      \n" "                                                              ░                                         ░                   \r\n"
#define MAX_IRC_CONNECTIONS 75
#define MAX_IRC_MSGLEN 512
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
		Server &operator=(const Server& copy);
		~Server();

		bool	CreateServer(const std::string &port, const std::string &pass);

	private:
		size_t		client_count;
		std::string password;
		std::vector<struct pollfd>c_fd_queue;
		std::vector<int>client_fds;
		void		OnServerLoop();
		std::string	OnServerFdQueue(void);
		void		CloseConnections();
		void		PreformServerCleanup();
		void		PopOutClientFd(int client_fd);
		bool		GenerateServerData(const std::string &port);
		void		InsertSocketFileDescriptorToPollQueue(const int connection_fd);
};
