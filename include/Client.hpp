/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiroux <pgiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:44:45 by pgiroux           #+#    #+#             */
/*   Updated: 2026/01/26 16:42:07 by pgiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Server.hpp"

class Server;
//class Channel;

class Client
{
	private:
		std::string _nickname;
		std::string _username;
		std::string	_hostname;
		std::string _client_addr;
		int			_fd;

	public:
		Client(int fd);
		Client(const Client &c);
		Client &operator=(const Client &rhs);
		//void	setClientAddr(std::string client_addr);
		~Client();
};


