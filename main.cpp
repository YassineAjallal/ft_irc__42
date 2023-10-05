/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 13:27:07 by hmeftah           #+#    #+#             */
/*   Updated: 2023/10/05 19:04:48 by yajallal         ###   ########.fr       */
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

Channel& test_channel(std::vector<Client>& clients)
{

	Channel *chan = new Channel("youtube");
	for (size_t i = 0; i < clients.size(); i++)
		chan->join(clients[i]);
	return (*chan);
}

void printMessage(std::vector<Client>& clients)
{
	for (size_t i = 0; i < clients.size(); i++)
		std::cout << clients[i].GetMessageBuffer() << "\n\n" << std::endl;
}

void topic_test (std::vector<Client>& clients, Channel chan)
{
	Client cl(100, 1);
	cl.SetName("yassine");
	chan.topic(cl, true, "programing");
	std::cout << cl.GetMessageBuffer() << std::endl;
	printMessage(clients);
}

int main(int __unused ac, char __unused **av) {
	std::vector<Client> clients;
	for (size_t i = 0; i < 4; i++)
	{
		clients.push_back(Client(i * 10, 1));
		clients[i].SetName(std::to_string(i * 10) + "\'cl");
	}
	Channel chan = test_channel(clients);
	topic_test(clients, chan);
	return 0;
}