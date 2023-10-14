/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 11:22:38 by hmeftah           #+#    #+#             */
/*   Updated: 2023/10/14 09:50:08 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <vector>


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
    void    						setCommand(std::string command);
    void    						setArgs(std::vector<std::string> args);
    void    						setTarget(std::vector<std::string> target);
    void    						setMessage(std::string message);
    void    						setType(CommandType type);
    
    /* Getters */
    const std::string 					&getCommand() const;
    const std::vector<std::string>		&getArgs() const;
    const std::vector<std::string>		&getTarget() const;
    const std::string 					&getMessage() const;
	Client&								getClient() const;
    CommandType							getType() const;
    
  private:
    Client& 						client;
    std::string 					command;
    std::vector<std::string> 			args;
    std::vector<std::string> 			target;
    std::string 					message;
    CommandType 					type;
};