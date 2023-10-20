/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Toolkit.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 15:33:48 by hmeftah           #+#    #+#             */
/*   Updated: 2023/10/18 10:54:44 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
class Client;
void		_bzero(void *ptr, size_t size);
void		_memset(void *ptr, void *ptr2, size_t size);
size_t		_strlen(const char *str);
std::string	_user_info(Client& client, bool info_type);