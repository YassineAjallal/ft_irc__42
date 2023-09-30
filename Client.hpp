/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:21:36 by hmeftah           #+#    #+#             */
/*   Updated: 2023/09/29 17:17:15 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <iterator>
#include <iostream>
#include <string>

class Client
{
	private:
		std::string	 	name;
		int	 			socket_id;
		//int  channel_id;
		bool 			just_connected;
		bool			should_be_kicked;
		std::string		raw_data;
		//bool			IsOperator;
		
	public:
		Client();
		Client(const Client& copy);
		Client(int socket_id, bool just_connected);
		Client &operator=(const Client& copy);
		~Client();

		int			getSockID() const;
		bool		ShouldBeKicked() const;
		void		SetKickStatus(bool status);
		int			JustConnectedStatus() const;
		const std::string&	GetBuffer(void) const;
		void		SetName(const std::string& name);
		void		SetJustConnectedStatus(bool status);
		void		SetBuffer(const std::string& buffer);
};
