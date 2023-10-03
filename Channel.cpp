/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:11:18 by yajallal          #+#    #+#             */
/*   Updated: 2023/10/03 19:35:12 by yajallal         ###   ########.fr       */
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
	// if (std::find(this->_members.begin(), this->_members.end(), client.getSockID()) != this->_members.end())
	// 	client.SetMessage(client.getName() + " " + this->_name + " :You are already in this channel\r\n");
	// else
	// {
		// std::cout << this->_operators.size() << std::endl;
		if (this->_operators.size() == 0)
		{
			this->_operators.push_back(std::make_pair("~", client));
			client.SetMessage(
				client.getName() + " :is joining the channel\r\n" + 
				(this->_topic.empty() ? "" : RPL_TOPIC(client.getName(), this->_name, this->_topic)
					+ RPL_TOPICWHOTIME(this->_topic_setter, this->_name, this->_topic, this->_time_topic_is_set)) +
				this->show_users(client) +
				RPL_ENDOFNAMES(client.getName(), this->_name)
			);
		}
		else if (this->_members.size() < this->_size)
		{
			this->_members.push_back(std::make_pair("", client));
			client.SetMessage(
				client.getName() + " :is joining the channel\r\n" + 
				(this->_topic.empty() ? "" : RPL_TOPIC(client.getName(), this->_name, this->_topic)
					+ RPL_TOPICWHOTIME(this->_topic_setter, this->_name, this->_topic, this->_time_topic_is_set)) +
				this->show_users(client) +
				RPL_ENDOFNAMES(client.getName(), this->_name)
			);
		}
		else
		{

		}

	// }
}

// void Channel::part(int client_fd, std::string reason)
// {

// }

std::string		Channel::show_users(Client client) const
{
	std::string users;
	for(size_t i = 0; i < this->_operators.size(); i++)
		users += RPL_NAMREPLY(client.getName(), "=", this->_name, this->_operators[i].first, this->_operators[i].second.getName());
	for(size_t i = 0; i < this->_members.size(); i++)
		users += RPL_NAMREPLY(client.getName(), "=", this->_name, this->_members[i].first, this->_members[i].second.getName());
	users += "\r\n";
	return (users);
}
