/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:11:18 by yajallal          #+#    #+#             */
/*   Updated: 2023/10/05 18:02:07 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

// Constructors

Channel::Channel(const std::string& name) :
_name(name),
_size(5),
_has_password(false)
{}

Channel::Channel(const std::string& name, const std::string& password) :
_name(name),
_size(5),
_has_password(true),
_password(password)
{}

// Destructor
Channel::~Channel()
{
    
}

std::string 	Channel::getName() const
{
	return (this->_name);
}

std::string 	Channel::getPassword() const
{
	return (this->_password);
}

void			Channel::setPassword(const std::string& new_password)
{
	this->_password = new_password;
}
bool 			Channel::getHasPassword() const
{
	return (this->_has_password);
}

void			Channel::setHasPassword(bool b)
{
	this->_has_password = b;
}

size_t			Channel::getSize() const
{
	return (this->_size);
}

void			Channel::setSize(const size_t& s)
{
	this->_size = s;
}

std::string		Channel::getTopic() const
{
	return (this->_topic);
}

void			Channel::setTopic(const std::string& t, std::string setterName)
{
	this->setTopicSetter(setterName);
	this->setTopicTime(this->_get_time());
	this->_topic = t;
}

void			Channel::setTopicSetter(const std::string& ts)
{
	this->_topic_setter = ts;
}

void			Channel::setTopicTime(const std::string& tt)
{
	this->_time_topic_is_set = tt;
}

bool			Channel::getInviteOnly() const
{
	return (this->_invite_only);
}

void			Channel::setInviteOnly(bool b)
{
	this->_invite_only = b;
}

bool			Channel::operator==(const Channel& c)
{
	return (this->_name == c.getName());
}

bool			Channel::operator!=(const Channel& c)
{
	return (this->_name != c.getName());
}

bool			Channel::_on_channel(Client &client)
{
	return (std::find(this->_members.begin(), this->_members.end(), client) != this->_members.end());
}

void			Channel::sendToAll(Client &client, std::string msg)
{
	for (size_t i = 0; i < this->_members.size(); i++)
		if (this->_members[i] != client)
			this->_members[i].getClient()->SetMessage(msg);
}
void			Channel::_add_member(Client &client, bool role)
{
	this->_members.push_back(Member(client, role, role, role));
}

void			Channel::_remove_member(Client &client)
{
		this->_members.erase(std::remove(this->_members.begin(), this->_members.end(), client));
}

void 			Channel::join(Client &client)
{
	if (this->_on_channel(client))
		client.SetMessage(client.getName() + " " + this->_name + " :You are already in this channel\r\n");
	else
	{
		if (this->_members.size() >= this->_size)
			client.SetMessage(ERR_CHANNELISFULL(client.getName(), this->_name));
		else
		{
			if (this->_members.size() == 0)
				this->_add_member(client, true);
			else
				this->_add_member(client, false);
			client.SetMessage(
				client.getName() + " :is joining the channel\r\n" + 
				(this->_topic.empty() ? "" : RPL_TOPIC(client.getName(), this->_name, this->_topic) + RPL_TOPICWHOTIME(this->_topic_setter, this->_name, this->_topic, this->_time_topic_is_set)) +
				this->show_users(client) +
				RPL_ENDOFNAMES(client.getName(), this->_name)
			);
		}
	}
}

void 			Channel::part(Client &client, std::string reason)
{
	if (!this->_on_channel(client))
		client.SetMessage(ERR_NOTONCHANNEL(client.getName(), this->_name));
	else
	{
		this->_remove_member(client);
		client.SetMessage("leave channel \"&" + this->_name + "\"\r\n");
		this->sendToAll(client, client.getName() + " has leave " + this->_name + " because " + reason + "\r\n");
	}
}

std::string		Channel::_get_time()
{
	time_t		current_time;
	struct tm*	time_info;

	current_time = time(NULL);
	time_info = localtime(&current_time);
	return ("time");
	// return (time_info->tm_mday + "-" + (time_info->tm_mon + 1) + "-" + time_info->tm_year + 
	// 		" at " + time_info->tm_hour + ":" + time_info->tm_min);
}

void 			Channel::kick(Client &client, Client &kicked, std::string reason)
{
	std::vector<Member>::iterator it;
	if (!this->_on_channel(client))
		client.SetMessage(ERR_NOTONCHANNEL(client.getName(), this->_name));
	else
	{
		it = std::find(this->_operators.begin(), this->_operators.end(), client);
		if (!(*it).getOperatorPrev())
			client.SetMessage(ERR_CHANOPRIVSNEEDED(client.getName(), this->_name));
		else if (!this->_on_channel(kicked))
			client.SetMessage(ERR_USERNOTINCHANNEL(client.getName(), kicked.getName(), this->_name));
		else
		{
			this->_remove_member(kicked);
			kicked.SetMessage("You have been kicked from " + this->_name + " by " + client.getName() + " because " + (reason.empty() ? "bad content" : reason) + "\r\n");
			this->sendToAll(kicked, kicked.getName() + " has been kicked from " + this->_name + " by " + client.getName() + " because " + (reason.empty() ? "bad content" : reason) + "\r\n");
		}
	}
}

// void			Channel::mode(Client &client, std::string mode)
// {
	
// }

void			Channel::topic(Client &client, bool topic_exist, std::string topic)
{
	if (!this->_on_channel(client))
		client.SetMessage(ERR_NOTONCHANNEL(client.getName(), this->name));
	else
	{
		if (!topic_exist)
			client.SetMessage(this->_has_topic 
								? RPL_TOPIC(client.getName(), this->_name, this->_topic)
								: RPL
							)
	}
}

std::string		Channel::show_users(Client client) const
{
	std::string users;
	users += client.getName() + " = " + this->_name + " :";
	// for(size_t i = 0; i < this->_operators.size(); i++)
	// 	users += RPL_NAMREPLY((i == 0 ? "~@" : "@"), this->_operators[i].getClient().getName());

	/* -------------- print previliges !!!!!! --------- */

	for(size_t i = 0; i < this->_members.size(); i++)
		users += RPL_NAMREPLY("", this->_members[i].getClient()->getName());
	users += "\r\n";
	return (users);
}
