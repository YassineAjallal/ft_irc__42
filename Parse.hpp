/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 11:22:38 by hmeftah           #+#    #+#             */
/*   Updated: 2023/10/11 17:23:07 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <vector>

using std::string;

class Client;

enum CommandType {
    MSGINCLUDED,
    MSGNOTINCLUDED,
};

class Parse {
  public:
    Parse(Client& client);
    Parse(const Parse& src);
    Parse& operator=(const Parse& src);
    ~Parse();
    
    /* Setters */
    void    setCommand(string command);
    void    setArgs(std::vector<string> args);
    void    setTarget(std::vector<string> target);
    void    setMessage(string message);
    void    setType(CommandType type);
    
    /* Getters */
    const string 				&getCommand() const;
    const std::vector<string>	&getArgs() const;
    const std::vector<string>	&getTarget() const;
    const string 				&getMessage() const;
	Client&						getClient() const;
    CommandType					getType() const;
    
  private:
    Client& client;
    string command;
    std::vector<string> args;
    std::vector<string> target;
    string message;
    CommandType type;
};