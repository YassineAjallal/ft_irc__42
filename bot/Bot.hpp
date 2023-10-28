/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairou <mkhairou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:08:42 by mkhairou          #+#    #+#             */
/*   Updated: 2023/10/11 18:24:00 by mkhairou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
#define BOT_HPP

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include "../Client.hpp"
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <algorithm>
#include <signal.h>

class Bot : public AddressDataClient
{
private:

	int socket_id;
	std::string name;
	std::vector<std::string> jokes;
	std::vector<std::string> facts;
	std::vector<std::string> Forbidden_msg;
	std::string help_message;
	std::string buffer;
	std::string cmd;
	std::string user;
	std::string admin;
	std::string sender;
	void init_jokes();
	void init_facts();
	void init_help();
	void print_help();
	void print_version();
	void print_joke();
	void print_date();
	void print_math();
	void print_roll();
	void print_fact();
	void bot_main(std::vector<std::string> &commands);
	void parse_command(std::string command);
	void check_conversation(std::vector<std::string> &conversation);
	void join_channesl();
public:
	Bot(const std::string &port, const std::string &pass);
	void run_bot();
	void send_quit();
	~Bot();

};


#endif
