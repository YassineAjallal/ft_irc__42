/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:11:18 by yajallal          #+#    #+#             */
/*   Updated: 2023/10/14 15:08:27 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

// Constructors

Channel::Channel(const std::string& name) :
_name(name),
_size(5),
_has_password(false),
_invite_only(false)
{}

Channel::Channel(const std::string& name, const std::string& password) :
_name(name),
_size(5),
_has_password(true),
_invite_only(false),
_password(password)
{}

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

void			Channel::setPassword(const std::string& new_password, bool has_password)
{
	this->_password = new_password;
	this->_has_password = has_password;
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

void			Channel::setSize(const int& s)
{
	this->_size = (s > MAX_SIZE ? MAX_SIZE : s);
}

std::string		Channel::getTopic() const
{
	return (this->_topic);
}

void			Channel::_set_topic(const std::string& t, std::string setterName)
{
	this->setTopicSetter(setterName);
	this->setTopicTime(this->_get_time());
	this->_has_topic = true;
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

bool			Channel::operator==(const std::string& c)
{
	return (this->_name == c);
}

bool			Channel::operator!=(const std::string& c)
{
	return (this->_name != c);
}

bool			Channel::_on_channel(Client &client)
{
	// std::cout << ((std::find(this->_members.begin(), this->_members.end(), client) != this->_members.end()) ? "Found":"Not Found") << std::endl;
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
	std::string messageToSend;
	if (this->_on_channel(client))
		client.SetMessage(client.getName() + " " + this->_name + " :You are already in this channel\r\n");
	else if (this->_invite_only && 
				(std::find(this->_invited.begin(), this->_invited.end(), client) == this->_invited.end()))
		client.SetMessage(ERR_INVITEONLYCHAN(client.getName(), this->_name) + "\r\n");
	else
	{
		if ((int)this->_members.size() >= this->_size && this->_size != -1)
			client.SetMessage(ERR_CHANNELISFULL(client.getName(), this->_name) + "\r\n");
		else
		{
			if (this->_members.size() == 0)
				this->_add_member(client, true);
			else
				this->_add_member(client, false);
	
			messageToSend += ":" + client.getNick() + "!" + client.getName() + "@" + client.getHostname() + " JOIN " + this->_name + " * :" + client.getRealname() + "\r\n";
			messageToSend += (this->_topic.empty() ? "" : ( ":" + client.getServername() + " " + RPL_TOPIC(client.getNick(), this->_name, this->_topic) ));
			messageToSend += (this->_topic.empty() ? "" : ( ":" + client.getServername() + " " + RPL_TOPICWHOTIME(client.getNick(), this->_name, this->_topic_setter, this->_time_topic_is_set) ));
			messageToSend += ":" + client.getServername() + " " + this->showUsers(client);
			messageToSend += ":" + client.getServername() + " " + RPL_ENDOFNAMES(client.getNick(), this->_name);
			client.SetMessage(messageToSend);
			messageToSend = ":" + client.getNick() + "!" + client.getName() + "@" + client.getHostname() + " JOIN " + this->_name + " * :" + client.getRealname() + "\r\n";
			this->sendToAll(client, messageToSend);
		}
	}
}

void 			Channel::part(Client &client, std::string reason)
{
	if (!this->_on_channel(client))
		client.SetMessage(ERR_NOTONCHANNEL(client.getName(), this->_name) + "\r\n");
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
		client.SetMessage(ERR_NOTONCHANNEL(client.getName(), this->_name) + "\r\n");
	else
	{
		it = std::find(this->_members.begin(), this->_members.end(), client);
		if (it->getOperatorPrev())
			client.SetMessage(ERR_CHANOPRIVSNEEDED(client.getName(), this->_name) + "\r\n");
		else if (!this->_on_channel(kicked))
			client.SetMessage(ERR_USERNOTINCHANNEL(client.getName(), kicked.getName(), this->_name) + "\r\n");
		else
		{
			this->_remove_member(kicked);
			kicked.SetMessage("You have been kicked from " + this->_name + " by " + client.getName() + " because " + (reason.empty() ? "bad content" : reason) + "\r\n");
			this->sendToAll(kicked, kicked.getName() + " has been kicked from " + this->_name + " by " + client.getName() + " because " + (reason.empty() ? "bad content" : reason) + "\r\n");
		}
	}
}

void			Channel::_channel_mode(Client &client, bool add_remove, std::pair<std::string, std::string> mode)
{
	std::vector<Member>::iterator client_it;

	client_it = std::find(this->_members.begin(), this->_members.end(), client);
	if (!this->_on_channel(client))
		client.SetMessage(ERR_NOTONCHANNEL(client.getName(), this->_name) + "\r\n");
	else if (!client_it->getOperatorPrev())
		client.SetMessage(ERR_CHANOPRIVSNEEDED(client.getName(), this->_name) + "\r\n");
	else
	{
		if (mode.first == "i")
			this->_invite_only = add_remove;
		else if (mode.first == "k")
			this->setPassword(mode.second, add_remove);
		else if (mode.first == "l")
			this->_size = (add_remove ? atoi(mode.second.c_str()) : -1);
	}
	
}

void			Channel::_member_mode(Client &client, bool add_remove, std::string mode, Client& member)
{
	std::vector<Member>::iterator member_it;
	std::vector<Member>::iterator client_it;

	member_it = std::find(this->_members.begin(), this->_members.end(), member);
	client_it = std::find(this->_members.begin(), this->_members.end(), client);
	if (!this->_on_channel(client))
		client.SetMessage(ERR_NOTONCHANNEL(client.getName(), this->_name) + "\r\n");
	else if (!client_it->getOperatorPrev())
		client.SetMessage(ERR_CHANOPRIVSNEEDED(client.getName(), this->_name) + "\r\n");
	else
	{
		if (member_it == this->_members.end())
			client.SetMessage(ERR_USERNOTINCHANNEL(client.getName(), member.getName(), this->_name) + "\r\n");
		else if (mode == "o")
			member_it->setOperatorPrev(add_remove);
		else if (mode == "t")
			member_it->setTopicPrev(add_remove);
	}
}

void			Channel::invite(Client& client, Client &invited)
{
	std::vector<Member>::iterator client_it;
	std::vector<Member>::iterator invited_it;

	client_it = std::find(this->_members.begin(), this->_members.end(), client);
	invited_it = std::find(this->_members.begin(), this->_members.end(), invited);
	if (!this->_on_channel(client))
		client.SetMessage(ERR_NOTONCHANNEL(client.getName(), this->_name) + "\r\n");
	else if (this->_invite_only && !client_it->getOperatorPrev())
		client.SetMessage(ERR_CHANOPRIVSNEEDED(client.getName(), this->_name) + "\r\n");
	else if (invited_it != this->_members.end())
		client.SetMessage(ERR_USERONCHANNEL(client.getName(), invited.getName(), this->_name) + "\r\n");
	else
	{
		this->_invited.push_back(invited);
		client.SetMessage(RPL_INVITING(client.getName(), invited.getName(), this->_name) + "\r\n");
		invited.SetMessage("INVITE " + client.getName() + "\r\n");
	}
}

void			Channel::topic(Client &client, bool topic_exist, std::string topic)
{
	std::vector<Member>::iterator client_it;
	client_it = std::find(this->_members.begin(), this->_members.end(), client);
	if (!this->_on_channel(client))
		client.SetMessage(ERR_NOTONCHANNEL(client.getName(), this->_name) + "\r\n");
	else if (!topic_exist)
			client.SetMessage(this->_has_topic 
								? RPL_TOPIC(client.getName(), this->_name, this->_topic) +
									RPL_TOPICWHOTIME(client.getName(), this->_name, this->_topic_setter, this->_time_topic_is_set)
								: RPL_NOTOPIC(client.getName(), this->_name) + "\r\n"
							);
	else
	{
		if (!client_it->getTopicPrev())
			client.SetMessage(ERR_CHANOPRIVSNEEDED(client.getName(), this->_name) + "\r\n");
		else
		{
			this->_set_topic(topic, client.getName());
			client.SetMessage("TOPIC " + this->_topic + "\r\n");
			this->sendToAll(client, "TOPIC " + this->_topic + "\r\n");
		}
	}
	
}
void			Channel::who(Client &client)
{
	std::string who_reply;
	for (size_t i = 0; i < this->_members.size(); i++)
	{
		who_reply += ":" + client.getServername() + " ";
		who_reply += RPL_WHOREPLY(client.getNick(), 
								  this->_name,
								  this->_members[i].getClient()->getName(), 
								  this->_members[i].getClient()->getHostname(), 
								  this->_members[i].getClient()->getServername(), 
								  this->_members[i].getClient()->getNick(), 
								  this->_members[i].getClient()->getRealname());
	}
	who_reply += ":" + client.getServername() + " " + RPL_ENDOFWHO(client.getNick(), this->_name);
	client.SetMessage(who_reply);
}
std::string		Channel::showUsers(Client& client) const
{
	std::string users;
	users += "353 " + client.getNick() + " = " + this->_name + " :";
	for(size_t i = 0; i < this->_members.size(); i++)
		users += this->_members[i].getClient()->getNick() + "!~" + this->_members[i].getClient()->getName() + "@" + this->_members[i].getClient()->getHostname() + " ";
	users += "\r\n";
	return (users);
}

std::string		Channel::_members_prefixes(const Member& member) const
{
	std::string prefixes;
	prefixes += member.getFounderPrev() ? "~" : "";
	prefixes += member.getOperatorPrev() ? "@" : "";
	return (prefixes);
}