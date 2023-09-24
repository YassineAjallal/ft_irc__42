/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Auth.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 19:01:16 by hmeftah           #+#    #+#             */
/*   Updated: 2023/09/24 19:32:54 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>

class Auth
{
	public:
		Auth();

		static bool Authenticate(const std::string& buffer, const std::string& original_pass);

	private:
		Auth(const Auth& copy);
		Auth &operator=(const Auth& copy);
		~Auth();
		
		static const std::string getNick(const std::string &buf);
		static const std::string getPass(const std::string &buf);
		
};
