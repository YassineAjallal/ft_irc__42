/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 13:27:07 by hmeftah           #+#    #+#             */
/*   Updated: 2023/10/04 19:02:36 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <iostream>
#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Server.hpp"
#include "Channel.hpp"

/*
	- Ports under 1024 are reserved
	and don't go over 65535 port number.
	
	- Make sure to check if the port
	doesn't contain invalid characters.

	- Make sure to initialize all variables
	inside Server Class.

	- Make sure to check password for spaces
*/

int main(int __unused ac, char __unused **av) {
	// if (ac == 3) {
	// 	Server ServerHandler;
	// 	if (ServerHandler.CreateServer(av[1], av[2]))
	// 		return 1;
	// }
	// else {
	// 	std::cerr << "GUIDE: ./ircserv port password" << std::endl;
	// 	return 2;
	// }
	// Channel chan("youtube", false, "", "prog", 5);
	// std::vector<Client> clients;
	// for (int i = 0; i < 5; i++)
	// {
	// 	clients.push_back(Client(i * 10, 1));
	// 	clients[i].SetName(std::to_string(i * 10) + "\'client");
	// }
	// for (int i = 0; i < 5; i++)
	// {
	// 	chan.join(clients[i]);
	// 	std::cout << clients[i].GetMessageBuffer();
	// 	std::cout << "------------------------------------------" << std::endl;
	// }
	// std::cout << "\n\n\n" << std::endl;
	// Client a(200, 1);
	// a.SetName("yajallal");
	// chan.part(a, "anti pointers", clients);
	// std::cout << a.GetMessageBuffer();
	// for (int i = 0; i < 5; i++)
	// {
	// 	std::cout << clients[i].GetMessageBuffer();
	// 	std::cout << "------------------------------------------" << std::endl;
	// }
	return 0;
}