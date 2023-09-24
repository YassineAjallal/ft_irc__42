/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Toolkit.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeftah <hmeftah@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 15:33:01 by hmeftah           #+#    #+#             */
/*   Updated: 2023/09/24 17:25:28 by hmeftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

void	_bzero(void *ptr, size_t size) {

	if (ptr) {
		for (size_t i = 0; i < size; i++) {
			*((char *)ptr + i) = 0;
		}
	}
}

void	_memset(void *ptr, void *ptr2, size_t size) {
	if (ptr) {
		for (size_t i = 0; i < size; i++) {
			*((char *)ptr + i) = *((char *)ptr2 + i);
		}
	}
}

size_t	_strlen(const char *str) {
	size_t len = 0;
	if (!str)
		return 0;
	while (str[len]) { len++; }
	return len;
}