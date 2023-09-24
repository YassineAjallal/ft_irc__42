/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Auth.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 19:04:11 by hmeftah           #+#    #+#             */
/*   Updated: 2023/09/24 19:42:03 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Auth.hpp"

Auth::Auth() {}
Auth::Auth(const Auth& copy) { (void)copy; }
Auth &Auth::operator=(const Auth& copy) { (void)copy; return (*this);}
Auth::~Auth() {}

const std::string Auth::getNick(const std::string &buf) {
	size_t oldpos = 0, pos = buf.find("NICK");
	if (pos == std::string::npos) {
		pos = buf.find("USER");
		if (pos == std::string::npos) {
			return "";
		}
	} else {
		oldpos = pos++;
		pos = buf.find(" ", pos);
		if (pos == std::string::npos) {
			pos = buf.find("\r\n", oldpos);
		}
	}
	std::cout << "U " << buf.substr(oldpos++, pos) << " U" << std::endl;
	return buf.substr(oldpos++, pos);
}

const std::string Auth::getPass(const std::string &buf) {
	size_t oldpos = 0, pos = buf.find("PASS");
	if (pos == std::string::npos) {
		return "";
	}
	else {
		oldpos = pos++;
		buf.find("\r\n", pos);
		if (pos == std::string::npos) {
			return "";
		}
	}
	std::cout << "P " << buf.substr(oldpos++, pos) << " P" << std::endl;
	return buf.substr(oldpos++, pos);
}

bool Auth::Authenticate(const std::string& buffer, const std::string& original_pass) {
	std::string name, pass;

	name = getNick(buffer);
	pass = getPass(buffer);

	std::cout << "User [" + name + "] tried to authenticate using the following password: [" + pass + "]" << std::endl;

	if (pass != original_pass) {
		return 1;
	}
	return 0;
}