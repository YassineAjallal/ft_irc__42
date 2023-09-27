/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Auth.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 19:04:11 by hmeftah           #+#    #+#             */
/*   Updated: 2023/09/27 12:33:58 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Auth.hpp"

Auth::Auth() {}
Auth::Auth(const Auth& copy) { (void)copy; }
Auth &Auth::operator=(const Auth& copy) { (void)copy; return (*this);}
Auth::~Auth() {}


const std::string Auth::getPass(const std::string &buf) {
	size_t oldpos = 0, pos = buf.find("PASS");
	if (pos == std::string::npos) {
		return "";
	}
	else {
		oldpos = pos + 4;
		buf.find("\r\n", pos);
		if (pos == std::string::npos) {
			return "";
		}
	}
	return buf.substr(oldpos++, pos);
}

/*
	- Authenticates the user, returns 1 if the client gave the wrong password
*/
bool Auth::Authenticate(const std::string& buffer, const std::string& original_pass) {
	std::string name, pass;

	pass = getPass(buffer);

	if (pass != original_pass) {
		return 1;
	}
	return 0;
}