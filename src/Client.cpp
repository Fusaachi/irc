/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiroux <pgiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:44:48 by pgiroux           #+#    #+#             */
/*   Updated: 2026/02/09 14:57:00 by pgiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Client.hpp"


Client::Client(int fd) : _nickname(""), _username(""), _realname(""), _message(""), _hostname(""), _clientAddr(""), _fd(fd), _hasPwd(false), _hasNickname(false), _hasUsername(false), _register(false)
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


void Client::setNickname(std::string const &nickname)
{
	this->_nickname = nickname;
}

void	Client::setUsername(std::string const &username)
{
	this->_username = username;
}

void Client::setRealname(std::string const &realname)
{
	this->_realname = realname;
}

void Client::setMessage(std::string const &message)
{
	this->_message = message;
}

void Client::setHostname(std::string const &hostname)
{
	this->_hostname = hostname;
}

void Client::setClientAddr(std::string const &clientAddr)
{
	this->_clientAddr = clientAddr;
}

void Client::setFd(int fd)
{
	this->_fd = fd;
}

void Client::setHasNickname(bool boolean)
{
	this->_hasNickname = boolean;
}

void Client::setHasPassword(bool boolean)
{
	this->_hasPwd = boolean;
}

void Client::setIsRegister(bool boolean)
{
	this->_register = boolean;
}