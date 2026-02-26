/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfranke <pfranke@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 11:20:05 by pfranke           #+#    #+#             */
/*   Updated: 2026/02/26 11:32:40 by pfranke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP
#include <iostream>
#include <string>
#include <cstdlib>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

class Server
{
	private:
		int _port;
		std::string _password;
		int _fd;
	public:
		Server(int port, const std::string &password);
		~Server();
		void run();
		void closeConnection();
};

#endif