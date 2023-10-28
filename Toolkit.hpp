/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Toolkit.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 15:33:48 by hmeftah           #+#    #+#             */
/*   Updated: 2023/10/28 12:26:59 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <sys/time.h>
class Client;
void		_bzero(void *ptr, size_t size);
void		_memset(void *ptr, void *ptr2, size_t size);
size_t		_strlen(const char *str);
size_t      _gettime(void);
std::string	_user_info(Client& client, bool info_type);