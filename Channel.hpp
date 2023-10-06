/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:11:22 by yajallal          #+#    #+#             */
/*   Updated: 2023/10/06 11:25:03 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include "Client.hpp"
#include "Member.hpp"

#define MAX_SIZE 200
#define ERR_NEEDMOREPARAMS(client, command) ("(461) " + client + " " + command + " :Not enough parameters\r\n")
#define ERR_NOSUCHCHANNEL(client, channel) ("(403) " + client + " " + channel + " :No such channel\r\n")
#define ERR_TOOMANYCHANNELS(client, channel) ("(405) " + client + " " + channel + " :You have joined too many channels\r\n")
#define ERR_BADCHANNELKEY(client, channel) ("(475) " + client + " " + channel + " :Cannot join channel (+k)\r\n")
#define ERR_BANNEDFROMCHAN(client, channel) ("(474) ") + client + " " + channel + " :Cannot join channel (+b)\r\n")
#define ERR_CHANNELISFULL(client, channel) ("(471) " + client + " " + channel + " :Cannot join channel (+l)\r\n")
#define ERR_INVITEONLYCHAN(client, channel) ("(473) " + client + " " + channel + " :Cannot join channel (+i)\r\n")
#define ERR_BADCHANMASK(channel) ("(476) " + channel + " :Bad Channel Mask\r\n")
#define ERR_NOTONCHANNEL(client, channel) ("(442) " + client + " " + channel + " :You're not on that channel\r\n")
#define ERR_CHANOPRIVSNEEDED(client, channel) ("(482) " + client + " " + channel + " :You're not channel operator\r\n")
#define ERR_USERNOTINCHANNEL(client, nick, channel) ("(441)" + client + " " + nick + " " + channel +  " :They aren't on that channel\r\n")
#define ERR_USERONCHANNEL(client, nick, channel) ("(443) " + client + " " + nick + " " + channel + ":is already on channel\r\n")
#define ERR_INVITEONLYCHAN(client, channel) ("(473) " + client + " " + channel + " :Cannot join channel (+i)\r\n")

#define RPL_TOPIC(client, channel, topic) ("(332) " + client + " " + channel + ": " + topic + "\r\n")
#define RPL_NOTOPIC(client, channel) ("(331) " + client + " " + channel + " :No topic is set\r\n")
#define RPL_TOPICWHOTIME(client, channel, nick, setat) ("(333) " + client + " " + channel + " " + nick + " " + setat + "\r\n")
#define RPL_NAMREPLY(prefix, nick) (prefix + nick + " ")
#define RPL_ENDOFNAMES(client, channel) ("(366) " + client + " " + channel + " :End of /NAMES list\r\n")
#define RPL_INVITING(client, nick, channel) ("(341) " + client + " " + nick + " " + channel + "\r\n")



// numeric 
class Channel {
	public:
		Channel(const std::string& name); // has_pass = false, 
		Channel(const std::string& name, const std::string& password);
		~Channel();
		
		std::string 		getName() const;
		std::string 		getPassword() const;
		void				setPassword(const std::string& new_password, bool has_password);
		bool				getHasPassword() const;
		void				setHasPassword(bool b);
		size_t				getSize() const;
		void				setSize(const int& s);
		std::string			getTopic() const;
		void				setTopicSetter(const std::string& ts);
		void				setTopicTime(const std::string& tt);
		bool				getInviteOnly() const;
		void				setInviteOnly(bool b);

		void 				join(Client &client);
		void 				part(Client &client, std::string reason);
		void				kick(Client &client, Client &kicked, std::string reason);
		void				channel_mode(Client &client, bool add_remove, std::pair<std::string, std::string> mode);
		void				member_mode(Client &client, bool add_remove, std::string mode, Client& member);
		void				topic(Client &client, bool topic_exist, std::string topic);
		void				name();
		void				list();
		void				invite(Client& client, Client &invited);
		void				sendToAll(Client &client, std::string msg);
		std::string			show_users(Client client) const;
	
		bool				operator==(const Channel& c);
		bool				operator!=(const Channel& c);

	private:
		std::string 		_name;
		int					_size;
		bool				_has_password;
		bool				_invite_only;
		bool				_has_topic;
		std::string 		_password;
		std::string 		_topic;
		std::string 		_topic_setter;
		std::string 		_time_topic_is_set;
		std::vector<Client>	_invited;
		std::vector<Member>	_members;
		void				setTopic(const std::string& t, std::string setterName);
		bool				_on_channel(Client &client);
		void				_add_member(Client &client, bool role);
		void				_remove_member(Client &client);
		std::string			_get_time();
		std::string			_members_prefixes(const Member& member) const;
};

#endif // Channel_HPP


// print previliges in show_users function
// test the join function