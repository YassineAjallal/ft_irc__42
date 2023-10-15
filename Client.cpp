/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:28:13 by hmeftah           #+#    #+#             */
/*   Updated: 2023/10/15 13:05:46 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "Server.hpp"


Client::Client() :  nick(""), socket_id(-1), just_connected(0), should_be_kicked(0) { }

Client::Client(const Client& copy) : nick(copy.nick), socket_id(copy.getSockID()), just_connected(copy.JustConnectedStatus()), should_be_kicked(copy.should_be_kicked) {}

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
    Client();
    this->user_connected_date = time(NULL);
	this->socket_id = socket_id;
	this->just_connected = just_connected;
	
}

int Client::getSockID() const {
	return (this->socket_id);
}

int Client::JustConnectedStatus() const {
	return (this->just_connected);
}

void	Client::SetNick(const std::string& name) {
	this->nick = name;
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

void	Client::SetBuffer(const std::string& buffer) {
	this->raw_data.clear();
	this->raw_data = buffer;
}

const std::string&	Client::GetBuffer(void) const {
	return (this->raw_data);
}

const std::string&	Client::GetMessageBuffer(void) const {
	return (this->send_buffer);
}

void	Client::SetMessage(const std::string& buffer) {
	send_buffer = buffer;
}

const std::string& Client::GetName() const {
    return (this->nick);
}

void    Client::SetName(const std::string &name) {
    this->name = name;
}

void    Client::SetHostname(const std::string &hostname) {
    this->hostname = hostname;
}

void    Client::SetServername(const std::string &servername) {
    this->servername = servername;
}

void    Client::SetRealname(const std::string &realname) {
    this->realname = realname;
}

const std::string& Client::GetNameName() const {
    return this->name;
}

const std::string& Client::GetHostname() const {
    return this->hostname;
}

const std::string& Client::GetServername() const {
    return this->servername;
}

const std::string& Client::GetRealname() const {
    return this->realname;
}

unsigned long Client::GetConnectedDate() const {
    return (this->user_connected_date);
}