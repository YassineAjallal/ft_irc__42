/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:28:13 by hmeftah           #+#    #+#             */
/*   Updated: 2023/09/26 15:44:52 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"


Client::Client() :  name(""), socket_id(-1), just_connected(0) { }

Client::Client(const Client& copy) {
	(void)copy;
}

Client &Client::operator=(const Client& copy) {
	(void)copy;
	return *this;
}

Client::~Client()  {

}

Client::Client(int socket_id, bool just_connected) : socket_id(socket_id), just_connected(just_connected) {}

int Client::getSockID() const {
	return (this->socket_id);
}

int Client::JustConnectedStatus() const {
	return (this->just_connected);
}

void	Client::SetName(const std::string& name) {
	this->name = name;
}

void	Client::SetJustConnectedStatus(bool status) {
	this->just_connected = status;
}