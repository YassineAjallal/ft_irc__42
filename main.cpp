/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 13:27:07 by hmeftah           #+#    #+#             */
/*   Updated: 2023/10/03 19:32:11 by yajallal         ###   ########.fr       */
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
	Channel chan("youtube", 0, "", "programming", 122);
	Client client(10, 0);
	// std::cout << chan->getName() << std::endl;
	client.SetName("yassine");
	chan.join(client);
	std::cout << client.GetMessageBuffer();
	return 0;
}