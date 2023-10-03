/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 15:09:17 by hmeftah           #+#    #+#             */
/*   Updated: 2023/10/03 14:41:53 by yajallal         ###   ########.fr       */
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
#include <algorithm>
#include <ctime>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/poll.h>
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <sstream>
#include "Toolkit.hpp"

#define MAX_IRC_CONNECTIONS 75
#define MAX_SAME_CLIENT_CONNECTIONS 4
#define MAX_IRC_MSGLEN 4096
#define SRH 1

#define INTRO "Welcome to:\n" \
"	██████  ▄▄▄       ██▀███   ▄▄▄       ██░ ██     ██▓ ██▀███   ▄████▄       ██████ ▓█████  ██▀███   ██▒   █▓▓█████  ██▀███	\n" \
"▒██    ▒ ▒████▄    ▓██ ▒ ██▒▒████▄    ▓██░ ██▒   ▓██▒▓██ ▒ ██▒▒██▀ ▀█     ▒██    ▒ ▓█   ▀ ▓██ ▒ ██▒▓██░   █▒▓█   ▀ ▓██ ▒ ██▒ \n" \
"░ ▓██▄   ▒██  ▀█▄  ▓██ ░▄█ ▒▒██  ▀█▄  ▒██▀▀██░   ▒██▒▓██ ░▄█ ▒▒▓█    ▄    ░ ▓██▄   ▒███   ▓██ ░▄█ ▒ ▓██  █▒░▒███   ▓██ ░▄█ ▒ \n" \
"  ▒   ██▒░██▄▄▄▄██ ▒██▀▀█▄  ░██▄▄▄▄██ ░▓█ ░██    ░██░▒██▀▀█▄  ▒▓▓▄ ▄██▒     ▒   ██▒▒▓█  ▄ ▒██▀▀█▄    ▒██ █░░▒▓█  ▄ ▒██▀▀█▄   \n" \
"▒██████▒▒ ▓█   ▓██▒░██▓ ▒██▒ ▓█   ▓██▒░▓█▒░██▓   ░██░░██▓ ▒██▒▒ ▓███▀ ░   ▒██████▒▒░▒████▒░██▓ ▒██▒   ▒▀█░  ░▒████▒░██▓ ▒██▒ \n" \
"▒ ▒▓▒ ▒ ░ ▒▒   ▓▒█░░ ▒▓ ░▒▓░ ▒▒   ▓▒█░ ▒ ░░▒░▒   ░▓  ░ ▒▓ ░▒▓░░ ░▒ ▒  ░   ▒ ▒▓▒ ▒ ░░░ ▒░ ░░ ▒▓ ░▒▓░   ░ ▐░  ░░ ▒░ ░░ ▒▓ ░▒▓░ \n" \
"░ ░▒  ░ ░  ▒   ▒▒ ░  ░▒ ░ ▒░  ▒   ▒▒ ░ ▒ ░▒░ ░    ▒ ░  ░▒ ░ ▒░  ░  ▒      ░ ░▒  ░ ░ ░ ░  ░  ░▒ ░ ▒░   ░ ░░   ░ ░  ░  ░▒ ░ ▒░ \n" \
"░  ░  ░    ░   ▒     ░░   ░   ░   ▒    ░  ░░ ░    ▒ ░  ░░   ░ ░           ░  ░  ░     ░     ░░   ░      ░░     ░     ░░   ░  \n" \
"      ░        ░  ░   ░           ░  ░ ░  ░  ░    ░     ░     ░ ░               ░     ░  ░   ░           ░     ░  ░   ░      \n" \
"                                                              ░                                         ░                   \r\n"
#define DIE "Wrong password:\n" \
"██▄   ▄█ ▄███▄   \n" \
"█  █  ██ █▀   ▀  \n" \
"█   █ ██ ██▄▄    \n" \
"█  █  ▐█ █▄   ▄▀ \n" \
"███▀   ▐ ▀███▀   \n" \
"                \r\n"

class Client;

struct AddressData {
	protected:
		struct 	addrinfo	hints, *res;
		struct 	sockaddr_in	client_sock_data;
		socklen_t 			socket_data_size;
		int 				server_socket_fd;
};

class Server : public AddressData
{
	typedef void (Server::*function_to_command)(int);
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
		std::vector<Client> clients; // all clients connected
		// std::string commands[1]; // array of commands
		std::vector< function_to_command > functions_to_commands; // pointers to commands functios
		std::map< std::string , std::vector<int> > channels;
		std::vector<struct pollfd> c_fd_queue;
		std::vector<int> client_fds;
		std::string raw_data;
		std::string send_buffer;
		std::map<std::string, std::vector<std::string> > command;

		/* =============Server Functions============ */
		void		KickClients(void);
		void		OnServerLoop(void);
		void		OnServerFdQueue(void); // recieve command
		void		CloseConnections(void);
		int			FindClient(int client_fd);
		void		PreformServerCleanup(void);
		void		CopySockData(int client_fd);
		void		Authenticate(int client_fd);
		void		InsertClient(int client_fd);
		void		DeleteClient(int client_fd);
		void		ReadClientFd(int client_fd);
		bool		JustConnected(int socketfd);
		void		PopOutClientFd(int client_fd);
		void		SendClientMessage(int client_fd);
		bool		GenerateServerData(const std::string &port);
		void		InsertSocketFileDescriptorToPollQueue(const int connection_fd);

		/* ===============Interpreter================ */
		// void		PONG(int client_fd);
		void		JOIN(int client_fd);
		void		Interpreter(int client_fd); // parse command
		// void		FindCommand(int client_fd);
		
};
