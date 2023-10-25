/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:11:18 by yajallal          #+#    #+#             */
/*   Updated: 2023/10/25 13:08:44 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

// Constructors

Channel::Channel(const std::string& name) :
_name(name),
_size(5),
_has_password(false),
_invite_only(false),
_has_topic(false),
_topic_priv(true),
_creation_time(time(NULL))
{}

Channel::Channel(const std::string& name, const std::string& password) :
_name(name),
_size(5),
_has_password(true),
_invite_only(false),
_has_topic(false),
_topic_priv(true),
_password(password),
_creation_time(time(NULL))
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

bool			Channel::getTopicPriv() const
{
	return (this->_topic_priv);
}

void			Channel::setTopicPriv(bool b)
{
	this->_topic_priv = b;
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
	if (!this->_on_channel(client))
		this->_members.push_back(Member(client, role, role));
}

void			Channel::removeMember(Client &client)
{
	if (this->_on_channel(client))
		this->_members.erase(std::remove(this->_members.begin(), this->_members.end(), client));
}

void 			Channel::join(Client &client)
{
	std::string messageToSend;
	if (this->_invite_only && 
			(std::find(this->_invited.begin(), this->_invited.end(), client) == this->_invited.end()))
		client.SetMessage(ERR_INVITEONLYCHAN(client.getName(), this->_name) + "\r\n");
	else
	{
		if ((int)this->_members.size() >= this->_size && this->_size != -1)
			client.SetMessage(_user_info(client, true) + ERR_CHANNELISFULL(client.getName(), this->_name) + "\r\n");
		else
		{
			if (this->_members.size() == 0)
				this->_add_member(client, true);
			else
				this->_add_member(client, false);
	
			messageToSend += _user_info(client, true) + "JOIN " + this->_name + " * :" + client.getRealname() + "\r\n";
			messageToSend += (this->_topic.empty() ? "" : ( _user_info(client, false) + RPL_TOPIC(client.getNick(), this->_name, this->_topic) ));
			messageToSend += (this->_topic.empty() ? "" : ( _user_info(client, false) + RPL_TOPICWHOTIME(client.getNick(), this->_name, this->_topic_setter, this->_time_topic_is_set) ));
			messageToSend += _user_info(client, false) + this->showUsers(client);
			messageToSend += _user_info(client, false) + RPL_ENDOFNAMES(client.getNick(), this->_name);
			client.SetMessage(messageToSend);
			messageToSend = _user_info(client, true) + "JOIN " + this->_name + " * :" + client.getRealname() + "\r\n";
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
		this->removeMember(client);
		client.SetMessage("leave channel \"&" + this->_name + "\"\r\n");
		this->sendToAll(client, client.getName() + " has leave " + this->_name + " because " + reason + "\r\n");
	}
}

std::string		Channel::_get_time()
{
	time_t				current_time;
	std::stringstream 	ss;
	std::string			time_string;
	

	current_time = time(NULL);
	ss << current_time;
	ss >> time_string;
	std::cout << time_string << std::endl;
	return (time_string);
}

void 			Channel::kick(Client &client, Client &kicked, std::string reason)
{
	std::vector<Member>::iterator it;
	if (!this->_on_channel(client))
		client.SetMessage(_user_info(client, false) + ERR_NOTONCHANNEL(client.getName(), this->_name));
	else
	{
		it = std::find(this->_members.begin(), this->_members.end(), client);
		if (!it->getOperatorPriv())
			client.SetMessage(_user_info(client, false) + ERR_CHANOPRIVSNEEDED(client.getName(), this->_name));
		else if (!this->_on_channel(kicked))
			client.SetMessage(_user_info(client, false) + ERR_USERNOTINCHANNEL(client.getName(), kicked.getName(), this->_name));
		else
		{
			this->removeMember(kicked);
			if (this->_size != -1) 
				--this->_size;
			kicked.SetMessage(_user_info(client, true) + " KICK " + this->_name + " " + kicked.getNick() + " :" + (reason.empty() ? "bad content" : reason) + "\r\n");
			this->sendToAll(kicked, _user_info(client, true) + " KICK " + this->_name + " " + kicked.getNick() + " :" + (reason.empty() ? "bad content" : reason)  + "\r\n");
		}
	}
}

void			Channel::channelMode(Client &client, bool add_remove, char mode, std::string param)
{
	std::vector<Member>::iterator client_it;
	char	sign  = (add_remove ? '+' : '-');

	client_it = std::find(this->_members.begin(), this->_members.end(), client);
	if (!this->_on_channel(client))
		client.SetMessage(_user_info(client, false) + ERR_NOTONCHANNEL(client.getName(), this->_name) + "\r\n");
	else if (!client_it->getOperatorPriv())
		client.SetMessage(_user_info(client, false) + ERR_CHANOPRIVSNEEDED(client.getName(), this->_name) + "\r\n");
	else
	{
		if (mode == 'i' && this->_invite_only != add_remove)
		{
			this->_invite_only = add_remove;
			client.SetMessage(_user_info(client, true) + "MODE " + this->_name + " " + sign +mode + " "  + "\r\n");
			this->sendToAll(client, _user_info(client, true) + "MODE " + this->_name + " " + sign + mode + " "  + "\r\n");
		}
		else if (mode == 'l' && atoi(param.c_str()) != this->_size)
		{
			if (param.empty())
				client.SetMessage(_user_info(client, false) + ERR_NEEDMOREPARAMS(client.getNick(), "MODE " + sign + "l"));
			else
			{
				this->_size = (add_remove ? atoi(param.c_str()) : -1);
				client.SetMessage(_user_info(client, true) + "MODE " + this->_name + " " + sign + mode + " " + param + "\r\n");
				this->sendToAll(client, _user_info(client, true) + "MODE " + this->_name + " " + sign + mode + " " + param + "\r\n");
			}
		}
		else if (mode == 't' && this->_topic_priv != add_remove)
		{
			this->_topic_priv = add_remove;
			client.SetMessage(_user_info(client, true) + "MODE " + this->_name + " " + sign + mode + " "  + "\r\n");
			this->sendToAll(client, _user_info(client, true) + "MODE " + this->_name + " " + sign + mode + " "  + "\r\n");
		}
		else
		{
			if (param.empty())
				client.SetMessage(_user_info(client, false) + ERR_NEEDMOREPARAMS(client.getNick(), "MODE " + sign + "k"));
			else if (add_remove && this->_has_password)
				client.SetMessage(_user_info(client, false) + ERR_KEYSET(client.getNick(), this->_name));
			else
			{
				this->setPassword(param, add_remove);
				client.SetMessage(_user_info(client, true) + "MODE " + this->_name + " " + sign + mode + " " + param + "\r\n");
			this->sendToAll(client, _user_info(client, true) + "MODE " + this->_name + " " + sign + mode + " " + param + "\r\n");
			}
		}
	}
}

void			Channel::memberMode(Client &client, bool add_remove, char mode, Client& member)
{
	std::vector<Member>::iterator member_it;
	std::vector<Member>::iterator client_it;
	char	sign  = (add_remove ? '+' : '-');

	member_it = std::find(this->_members.begin(), this->_members.end(), member);
	client_it = std::find(this->_members.begin(), this->_members.end(), client);
	if (!this->_on_channel(client))
		client.SetMessage(_user_info(client, false) + ERR_NOTONCHANNEL(client.getName(), this->_name) + "\r\n");
	else if (!client_it->getOperatorPriv())
		client.SetMessage(_user_info(client, false) + ERR_CHANOPRIVSNEEDED(client.getName(), this->_name) + "\r\n");
	else
	{
		if (member_it == this->_members.end())
			client.SetMessage(_user_info(client, false) + ERR_USERNOTINCHANNEL(client.getName(), member.getName(), this->_name) + "\r\n");
		else if (mode == 'o')
		{
			member_it->setOperatorPriv(add_remove);
			client.SetMessage(_user_info(client, true) + "MODE " + this->_name + " " + sign + mode + " " + member.getNick() + "\r\n");
			this->sendToAll(client, _user_info(client, true) + "MODE " + this->_name + " " + sign + mode + " " + member.getNick() + "\r\n");
		}
	}
}

void			Channel::invite(Client& client, Client &invited)
{
	std::vector<Member>::iterator client_it;
	std::vector<Member>::iterator invited_it;

	client_it = std::find(this->_members.begin(), this->_members.end(), client);
	invited_it = std::find(this->_members.begin(), this->_members.end(), invited);
	if (!this->_on_channel(client))
		client.SetMessage(_user_info(client, false) + ERR_NOTONCHANNEL(client.getName(), this->_name));
	else if (this->_invite_only && !client_it->getOperatorPriv())
		client.SetMessage(_user_info(client, false) + ERR_CHANOPRIVSNEEDED(client.getName(), this->_name));
	else if (invited_it != this->_members.end())
		client.SetMessage(_user_info(client, false) + ERR_USERONCHANNEL(client.getName(), invited.getName(), this->_name));
	else
	{
		this->_invited.push_back(invited);
		client.SetMessage(_user_info(client, false) + RPL_INVITING(client.getName(), invited.getName(), this->_name));
		invited.SetMessage(_user_info(client, true) + "INVITE " + invited.getNick() + " " + this->_name + "\r\n");
	}
}

void			Channel::topic(Client &client, bool topic_exist, std::string topic)
{
	std::vector<Member>::iterator client_it;
	client_it = std::find(this->_members.begin(), this->_members.end(), client);
	if (!this->_on_channel(client))
		client.SetMessage(_user_info(client, false) + ERR_NOTONCHANNEL(client.getName(), this->_name));
	else if (!topic_exist)
	{
		if (this->_has_topic)
			client.SetMessage(_user_info(client, false) + RPL_TOPIC(client.getName(), this->_name, this->_topic) + 
							_user_info(client, false) + RPL_TOPICWHOTIME(client.getName(), this->_name, this->_topic_setter, this->_time_topic_is_set));
		else
			client.SetMessage(_user_info(client, false) +  RPL_NOTOPIC(client.getName(), this->_name));
	}
	else
	{
		if (!client_it->getOperatorPriv() && this->_topic_priv)
			client.SetMessage(_user_info(client, false) + ERR_CHANOPRIVSNEEDED(client.getName(), this->_name) + "\r\n");
		else
		{
			this->_set_topic(topic, client.getName());
			client.SetMessage(_user_info(client, true) + "TOPIC " + this->_name + " :" + this->_topic + "\r\n");
			this->sendToAll(client, _user_info(client, true) + "TOPIC " + this->_name + " :" + this->_topic + "\r\n");
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
								  (this->_members[i].getOperatorPriv() ? "@" : ""),
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
		users += (this->_members[i].getOperatorPriv() ? "@" : "")  + this->_members[i].getClient()->getNick() + " ";
	users += "\r\n";
	return (users);
}

std::string		Channel::_members_prefixes(const Member& member) const
{
	std::string prefixes;
	prefixes += member.getFounderPriv() ? "~" : "";
	prefixes += member.getOperatorPriv() ? "@" : "";
	return (prefixes);
}

void		 	Channel::mode(Client &client)
{
	std::string 		msg_to_send;
	std::stringstream	ss;
	std::string			creation_time;
	std::string			modes("+");

	ss << this->_creation_time;
	ss >> creation_time;
	modes += (this->_has_password ? "k" : "");
	modes += (this->_invite_only ? "i" : "");
	msg_to_send += ":" + client.getServername() + " ";
	msg_to_send += RPL_CHANNELMODEIS(client.getNick(), this->_name, modes);
	msg_to_send += ":" + client.getServername() + " ";
	msg_to_send += RPL_CREATIONTIME(client.getNick(), this->_name, creation_time);
	client.SetMessage(msg_to_send);
}

void			Channel::sendToOperators(Client &client, std::string msg)
{
	for (size_t i = 0; i < this->_members.size(); i++)
		if (this->_members[i] != client && this->_members[i].getOperatorPriv())
			this->_members[i].getClient()->SetMessage(msg);
}

void			Channel::sendToFounder(Client &client, std::string msg)
{
	for (size_t i = 0; i < this->_members.size(); i++)
		if (this->_members[i] != client && this->_members[i].getFounderPriv())
			this->_members[i].getClient()->SetMessage(msg);
}