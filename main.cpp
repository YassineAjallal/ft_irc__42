/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 13:27:07 by hmeftah           #+#    #+#             */
/*   Updated: 2023/09/25 10:10:55 by hmeftah          ###   ########.fr       */
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

/*
	- Ports under 1024 are reserved
	and don't go over 65535 port number.
	
	- Make sure to check if the port
	doesn't contain invalid characters.

	- Make sure to initialize all variables
	inside Server Class.
*/

int main(int ac, char **av) {
	if (ac == 3) {
		Server ServerHandler;
		if (ServerHandler.CreateServer(av[1], av[2]))
			return 1;
	}
	else {
		std::cerr << "GUIDE: ./ircserv port password" << std::endl;
		return 2;
	}
	return 0;
}