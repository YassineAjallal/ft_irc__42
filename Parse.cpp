/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 11:25:53 by hmeftah           #+#    #+#             */
/*   Updated: 2023/10/09 12:07:19 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "Parse.hpp"

Parse::Parse(Client& client) : client(client) {
    command = "";
    args.clear();
    target.clear();
    message = "";
}

Parse::Parse(const Parse& src) : client(src.client) {
    command = src.command;
    args = src.args;
    target = src.target;
    message = src.message;
}

Parse& Parse::operator=(const Parse& src) {
    if (this != &src) {
        command = src.command;
        args = src.args;
        target = src.target;
        message = src.message;
    }
    return (*this);
}

Parse::~Parse() {}

void    Parse::setCommand(string command) {
    this->command = command;
}

void    Parse::setArgs(std::vector<string> args) {
    this->args = args;
}

void    Parse::setTarget(std::vector<string> target) {
    this->target = target;
}

void    Parse::setMessage(string message) {
    this->message = message;
}

const string &Parse::getCommand() const {
    return(this->command);
}

const std::vector<string> &Parse::getArgs() const {
    return (this->args);
}

const std::vector<string> &Parse::getTarget() const {
    return(this->target);
}

const string &Parse::getMessage() const {
    return(this->message);
}

CommandType Parse::getType() const {
    return(this->type);
}

void    Parse::setType(CommandType type) {
    this->type = type;
}

Client&				Parse::getClient() const
{
	return (this->client);
}