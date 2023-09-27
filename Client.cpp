/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:28:13 by hmeftah           #+#    #+#             */
/*   Updated: 2023/09/27 12:21:41 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"


Client::Client() :  name(""), socket_id(-1), just_connected(0), should_be_kicked(0) { }

Client::Client(const Client& copy) : name(copy.name), socket_id(copy.getSockID()), just_connected(copy.JustConnectedStatus()), should_be_kicked(copy.should_be_kicked) {}

Client &Client::operator=(const Client& copy) {
	if (&copy != this) {
		name = copy.name;
		socket_id = copy.socket_id;
		just_connected = copy.just_connected;
		should_be_kicked = copy.should_be_kicked;
	}
	return *this;
}

Client::~Client()  {

}

Client::Client(int socket_id, bool just_connected) {
	this->socket_id = socket_id;
	this->just_connected = just_connected;
	
}

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

bool	Client::ShouldBeKicked(void) const {
	return (this->should_be_kicked);
}

void	Client::SetKickStatus(bool status) {
	this->should_be_kicked = status;
}