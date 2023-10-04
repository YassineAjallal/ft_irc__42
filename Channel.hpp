/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:11:22 by yajallal          #+#    #+#             */
/*   Updated: 2023/10/04 15:49:02 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Client.hpp"

#define ERR_NEEDMOREPARAMS(client, command) ("461 " + client + " " + command + " :Not enough parameters\r\n")
#define ERR_NOSUCHCHANNEL(client, channel) ("403 " + client + " " + channel + " :No such channel\r\n")
#define ERR_TOOMANYCHANNELS(client, channel) ("405 " + client + " " + channel + " :You have joined too many channels\r\n")
#define ERR_BADCHANNELKEY(client, channel) ("475 " + client + " " + channel + " :Cannot join channel (+k)\r\n")
#define ERR_BANNEDFROMCHAN(client, channel) ("474 " + client + " " + channel + " :Cannot join channel (+b)\r\n")
#define ERR_CHANNELISFULL(client, channel) ("471 " + client + " " + channel + " :Cannot join channel (+l)\r\n")
#define ERR_INVITEONLYCHAN(client, channel) ("473 " + client + " " + channel + " :Cannot join channel (+i)\r\n")
#define ERR_BADCHANMASK(channel) ("476 " + channel + " :Bad Channel Mask\r\n")
#define ERR_NOTONCHANNEL(client, channel) ("442 " + client + " " + channel + " :You're not on that channel\r\n")



#define RPL_TOPIC(client, channel, topic) ("332 " + client + " " + channel + ": " + topic + "\r\n")
#define RPL_TOPICWHOTIME(client, channel, nick, setat) ("333 " + client + " " + channel + " " + nick + " " + setat + "\r\n")
#define RPL_NAMREPLY(prefix, nick) (prefix + nick + " ")
#define RPL_ENDOFNAMES(client, channel) ("366 " + client + " " + channel + " :End of /NAMES list\r\n")




// numeric 
class Channel {
	public:
		Channel(std::string name, bool has_password, std::string password, std::string topic, size_t size);
		~Channel();
		void 			join(Client &client);
		void 			part(Client &client, std::string reason, std::vector<Client>& clients);
		std::string 	getName() const;
		std::string 	getPassword() const;
		std::string		show_users(Client client) const;
		bool 			getHasPassword() const;

	private:
		size_t		_size;
		std::string _name;
		std::string _password;
		std::string _topic;
		std::string _topic_setter;
		std::string _time_topic_is_set;
		bool		_has_password;
		std::vector<Client> _operators;
		std::vector<Client> _members;

};

#endif // Channel_HPP
