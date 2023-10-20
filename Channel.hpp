/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:11:22 by yajallal          #+#    #+#             */
/*   Updated: 2023/10/18 13:50:46 by yajallal         ###   ########.fr       */
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
#include <sstream>
#include "Toolkit.hpp"

#define MAX_SIZE 200
#define ERR_NEEDMOREPARAMS(client, command)										("461 " + client + " " + command + " :Not enough parameters\r\n")
#define ERR_NOSUCHCHANNEL(client, channel) 										("403 " + client + " " + channel + " :No such channel\r\n")
#define ERR_TOOMANYCHANNELS(client, channel) 									("405 " + client + " " + channel + " :You have joined too many channels\r\n")
#define ERR_BADCHANNELKEY(client, channel) 										("475 " + client + " " + channel + " :Cannot join channel (+k)\r\n")
#define ERR_BANNEDFROMCHAN(client, channel) 									("474 " + client + " " + channel + " :Cannot join channel (+b)\r\n")
#define ERR_CHANNELISFULL(client, channel) 										("471 " + client + " " + channel + " :Cannot join channel (+l)\r\n")
#define ERR_INVITEONLYCHAN(client, channel) 									("473 " + client + " " + channel + " :Cannot join channel (+i)\r\n")
#define ERR_BADCHANMASK(channel) 												("476 " + channel + " :Bad Channel Mask\r\n")
#define ERR_NOTONCHANNEL(client, channel) 										("442 " + client + " " + channel + " :You're not on that channel\r\n")
#define ERR_CHANOPRIVSNEEDED(client, channel) 									("482 " + client + " " + channel + " :You're not channel operator\r\n")
#define ERR_USERNOTINCHANNEL(client, nick, channel) 							("441" + client + " " + nick + " " + channel +  " :They aren't on that channel\r\n")
#define ERR_USERONCHANNEL(client, nick, channel) 								("443 " + client + " " + nick + " " + channel + " :is already on channel\r\n")
#define ERR_INVITEONLYCHAN(client, channel) 									("473 " + client + " " + channel + " :Cannot join channel (+i)\r\n")
#define	ERR_KEYSET(client, channel)												("467 " + client + " " + channel + " :Channel key already set\r\n")
#define RPL_NOTOPIC(client, channel) 											("331 " + client + " " + channel + " :No topic is set\r\n")
#define RPL_TOPIC(client, channel, topic) 										("332 " + client + " " + channel + ":" + topic + "\r\n")
#define RPL_TOPICWHOTIME(client, channel, nick, setat) 							("333 " + client + " " + channel + " " + nick + " " + setat + "\r\n")
#define RPL_NAMREPLY(prefix, nick) 												(prefix + nick + " ")
#define RPL_ENDOFNAMES(client, channel) 										("366 " + client + " " + channel + " :End of /NAMES list\r\n")
#define RPL_INVITING(client, nick, channel) 									("341 " + client + " " + nick + " " + channel + "\r\n")


#define RPL_ENDOFWHO(client, mask) 												("315 " + client + " " + mask + " :End of WHO list\r\n")
#define RPL_WHOREPLY(client, channel, username, host, server, nick, realname)	("352 " + client + " " + channel + " " + username + " " + host + " " + server + " " + nick + " H 0 :" + realname + "\r\n")

#define RPL_CHANNELMODEIS(client, channel, modes)								("324 " + client + " " + channel + " " + modes + "\r\n")
#define RPL_CREATIONTIME(client, channel, creationtime)							("329 " + client + " " + channel + " " + creationtime + "\r\n")
// numeric 
class Channel {
	public:
		Channel(const std::string& name); // has_pass = false, 
		Channel(const std::string& name, const std::string& password);
		~Channel();
		
		// getters
		std::string 		getName() const;
		std::string 		getPassword() const;
		std::string			getTopic() const;
		bool				getHasPassword() const;
		bool				getInviteOnly() const;
		size_t				getSize() const;

		// setters
		void				setPassword(const std::string& new_password, bool has_password);
		void				setHasPassword(bool b);
		void				setSize(const int& s);
		void				setTopicSetter(const std::string& ts);
		void				setTopicTime(const std::string& tt);
		void				setInviteOnly(bool b);

		void 				join(Client &client);
		void 				part(Client &client, std::string reason);
		void				kick(Client &client, Client &kicked, std::string reason);
		void				topic(Client &client, bool topic_exist, std::string topic);
		void				who(Client &client); // execute when a client send " WHO #channel_name "
		void				invite(Client& client, Client &invited);
		void				sendToAll(Client &client, std::string msg);
		void				sendToOperators(Client &client, std::string msg);
		void				sendToFounder(Client &client, std::string msg);
		std::string			showUsers(Client& client) const;
		void		 		mode(Client &client);
		void				member_mode(Client &client, bool add_remove, std::string mode, Client& member);
		/* change the std::pair by target */
		void				channel_mode(Client &client, bool add_remove, std::string mode, std::string param);
	
		bool				operator==(const std::string& c);
		bool				operator!=(const std::string& c);

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
		time_t				_creation_time;
		std::vector<Client>	_invited;
		std::vector<Member>	_members;
		void				_set_topic(const std::string& t, std::string setterName);
		bool				_on_channel(Client &client);
		void				_add_member(Client &client, bool role);
		void				_remove_member(Client &client);
		std::string			_get_time();
		std::string			_members_prefixes(const Member& member) const;
};

#endif // Channel_HPP


// print previliges in show_users function
// test the join function