/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:11:18 by yajallal          #+#    #+#             */
/*   Updated: 2023/10/04 20:27:37 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

// Constructors
Channel::Channel(std::string name, bool has_password, std::string password, std::string topic, size_t size)
{
	this->_name = name;
	this->_has_password = has_password;
	this->_password = password;
	this->_topic = topic;
	this->_size = size;
}

// Destructor
Channel::~Channel()
{
    
}

std::string Channel::getName() const
{
	return (this->_name);
}

std::string Channel::getPassword() const
{
	return (this->_password);
}

bool 		Channel::getHasPassword() const
{
	return (this->_has_password);
}


void Channel::join(Client &client)
{
	if (std::find(this->_members.begin(), this->_members.end(), client) != this->_members.end() || 
		std::find(this->_operators.begin(), this->_operators.end(), client) != this->_operators.end() )
		client.SetMessage(client.getName() + " " + this->_name + " :You are already in this channel\r\n");
	else
	{
		if (this->_members.size() + this->_operators.size() >= this->_size)
			client.SetMessage(ERR_CHANNELISFULL(client.getName(), this->_name));
		else if (this->_operators.size() == 0)
		{
			this->_operators.push_back(client);
			client.SetMessage(
				client.getName() + " :is joining the channel\r\n" + 
				(this->_topic.empty() ? "" : RPL_TOPIC(client.getName(), this->_name, this->_topic) + RPL_TOPICWHOTIME(this->_topic_setter, this->_name, this->_topic, this->_time_topic_is_set)) +
				this->show_users(client) +
				RPL_ENDOFNAMES(client.getName(), this->_name)
			);
		}
		else
		{
			this->_members.push_back(client);
			client.SetMessage(
				client.getName() + " :is joining the channel\r\n" + 
				(this->_topic.empty() ? "" : RPL_TOPIC(client.getName(), this->_name, this->_topic) + RPL_TOPICWHOTIME(this->_topic_setter, this->_name, this->_topic, this->_time_topic_is_set)) +
				this->show_users(client) +
				RPL_ENDOFNAMES(client.getName(), this->_name)
			);
		}
	}
}

void Channel::part(Client &client, std::string reason, std::vector<Client>& clients)
{
	std::vector<Client>::iterator found_client;
	if (std::find(this->_members.begin(), this->_members.end(), client) == this->_members.end() && 
		std::find(this->_operators.begin(), this->_operators.end(), client) == this->_operators.end())
		client.SetMessage(ERR_NOTONCHANNEL(client.getName(), this->_name));
	else
	{
		if (std::find(this->_operators.begin(), this->_operators.end(), client) != this->_operators.end())
			this->_operators.erase(std::remove(this->_operators.begin(), this->_operators.end(), client));
		else
			this->_members.erase(std::remove(this->_members.begin(), this->_members.end(), client));
		client.SetMessage("leave channel \"&" + this->_name + "\"\r\n");
		for (size_t i = 0; i < this->_members.size(); i++)
		{
			found_client = std::find(clients.begin(), clients.end(), this->_members[i]);
			if (*(found_client) != client)
				(*found_client).SetMessage(client.getName() + " has leave " + this->_name + " because " + reason + "\r\n");
		}
		for (size_t i = 0; i < this->_operators.size(); i++)
		{
			found_client = std::find(clients.begin(), clients.end(), this->_operators[i]);
			if (*(found_client) != client)
				(*found_client).SetMessage(client.getName() + " has leave " + this->_name + " because " + reason + "\r\n");
		}
	}
}

void Channel::kick(Client &client, Client &kicked, std::string reason, std::vector<Client>& clients)
{
	std::vector<Client>::iterator found_client;
	if (std::find(this->_members.begin(), this->_members.end(), client) == this->_members.end() && 
		std::find(this->_operators.begin(), this->_operators.end(), client) == this->_operators.end())
		client.SetMessage(ERR_NOTONCHANNEL(client.getName(), this->_name));
	else
	{
		if (std::find(this->_operators.begin(), this->_operators.end(), client) == this->_operators.end())
			client.SetMessage(ERR_CHANOPRIVSNEEDED(client.getName(), this->_name));
		else if (std::find(this->_operators.begin(), this->_operators.end(), kicked) == this->_operators.end() &&
				std::find(this->_members.begin(), this->_members.end(), kicked) == this->_members.end())
			client.SetMessage(ERR_USERNOTINCHANNEL(client.getName(), kicked.getName(), this->_name));
		else
		{
			if (std::find(this->_operators.begin(), this->_operators.end(), kicked) != this->_operators.end())
				this->_operators.erase(std::remove(this->_operators.begin(), this->_operators.end(), kicked));
			else
				this->_members.erase(std::remove(this->_members.begin(), this->_members.end(), kicked));
			kicked.SetMessage("You have been kicked from " + this->_name + " by " + client.getName() + " because " + (reason.empty() ? "bad content" : reason) + "\r\n");
			for (size_t i = 0; i < this->_members.size(); i++)
			{
				found_client = std::find(clients.begin(), clients.end(), this->_members[i]);
				if (*(found_client) != kicked)
					(*found_client).SetMessage(kicked.getName() + " has been kicked from " + this->_name + " by " + client.getName() + " because " + (reason.empty() ? "bad content" : reason) + "\r\n");
			}
			for (size_t i = 0; i < this->_operators.size(); i++)
			{
				found_client = std::find(clients.begin(), clients.end(), this->_operators[i]);
				if (*(found_client) != kicked)
					(*found_client).SetMessage(kicked.getName() + " has been kicked from " + this->_name + " by " + client.getName() + " because " + (reason.empty() ? "bad content" : reason) + "\r\n");

			}
		}
	}
}

std::string		Channel::show_users(Client client) const
{
	std::string users;
	users += client.getName() + " = " + this->_name + " :";
	for(size_t i = 0; i < this->_operators.size(); i++)
		users += RPL_NAMREPLY((i == 0 ? "~@" : "@"), this->_operators[i].getName());
	for(size_t i = 0; i < this->_members.size(); i++)
		users += RPL_NAMREPLY("", this->_members[i].getName());
	users += "\r\n";
	return (users);
}
