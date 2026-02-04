/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiroux <pgiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:44:45 by pgiroux           #+#    #+#             */
/*   Updated: 2026/01/30 14:04:19 by pgiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Server.hpp"

class Server;
//class Channel;

class Client
{
	private:
		//std::string _nickname;
		//std::string _username;
		//std::string	_hostname;
		//std::string _client_addr;
		int			_fd;

	public:
		Client(int fd);
		Client(const Client &c);
		Client &operator=(const Client &rhs);
		int	getFd(){return _fd;};
		//void	setClientAddr(std::string client_addr);
		~Client();
};


