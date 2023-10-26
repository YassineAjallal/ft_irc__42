/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:21:36 by hmeftah           #+#    #+#             */
/*   Updated: 2023/10/26 11:32:01 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <iterator>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/time.h>
#include "Toolkit.hpp"

struct AddressDataClient {
	public:
		struct 	addrinfo	hints, *res;
		struct 	sockaddr_in	client_sock_data;
		socklen_t 			socket_data_size;
		int 				server_socket_fd;
};

struct ClientInfo {
    protected:
        std::string name;
        std::string hostname;
        std::string servername;
        std::string realname;
};

class Client : public AddressDataClient, public ClientInfo
{
	private:
		std::string	 	nick;
		int	 			socket_id;
		//int  channel_id;
		bool 			just_connected;
		bool			should_be_kicked;
		std::string		raw_data;
		std::string		send_buffer; // the message from server
		unsigned long   last_user_activity;
		
		//bool			IsOperator;
		
	public:
		Client();
		Client(const Client& copy);
		Client(int socket_id, bool just_connected);
		Client &operator=(const Client& copy);
		~Client();

		int					getSockID() const;
		bool				ShouldBeKicked() const;
		void				SetKickStatus(bool status);
		int					JustConnectedStatus() const;
		const std::string&	GetBuffer(void) const;
		void				SetJustConnectedStatus(bool status);
		std::string&		GetMessageBuffer(void);
		void				SetBuffer(const std::string& buffer);
		void				SetMessage(const std::string& buffer);

		void				SetNick(const std::string& name);
        void    			SetName(const std::string &name);
        void    			SetHostname(const std::string &hostname);
        void    			SetServername(const std::string &servername);
        void    			SetRealname(const std::string &realname);

        const std::string&	getNick() const;
        const std::string&	getName() const;
        const std::string&	getHostname() const;
        const std::string&	getServername() const;
        const std::string&	getRealname() const;
        
        size_t GetLastUserActivity() const;

		bool				operator==(const Client& c);
        bool                operator==(int c);
		bool				operator==(const std::string& s);
		bool				operator!=(const Client& c);
};

std::ostream& operator<<(std::ostream& os, Client &client);