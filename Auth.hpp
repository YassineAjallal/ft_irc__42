/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Auth.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 19:01:16 by hmeftah           #+#    #+#             */
/*   Updated: 2023/09/27 12:32:25 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>
#include "Client.hpp"

class Auth
{
	public:
		Auth();

		static bool Authenticate(const std::string& buffer, const std::string& original_pass);
		static const std::string getPass(const std::string &buf);

	private:
		Auth(const Auth& copy);
		Auth &operator=(const Auth& copy);
		~Auth();
		
		
};
