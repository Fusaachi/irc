/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiroux <pgiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:44:48 by pgiroux           #+#    #+#             */
/*   Updated: 2026/01/28 13:39:05 by pgiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Client.hpp"


Client::Client(int fd) : _fd(fd)/*, _nickname(""), _username(""), _hostname(""), _client_addr("")*/
{
}

Client::Client(const Client &c)
{
 	this->_fd  = c._fd;
}

Client& Client::operator=(const Client& rhs)
{
	if (this != &rhs)
		*this = rhs;
	return(*this);

}

Client::~Client()
{
}