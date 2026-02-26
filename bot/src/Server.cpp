/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfranke <pfranke@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 11:23:02 by pfranke           #+#    #+#             */
/*   Updated: 2026/02/26 11:34:32 by pfranke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

Server::Server(int port, const std::string &password) : _port(port), _password(password)
{
	std::cout << "Server created on port " << _port << " with password " << _password << std::endl;
}

Server::~Server()
{
	std::cout << "Server on port " << _port << " is being destroyed." << std::endl;
}

void Server::run()
{
	int new_socket;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	
	if ((_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) //socket creation
	{
		std::cerr << "Socket failed" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	if (setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) //set socket options
	{
		std::cerr << "setsockopt failed" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(_port);

	if (bind(_fd, (struct sockaddr *)&address, sizeof(address)) < 0) //bind socket to address
	{
		std::cerr << "Bind failed" << std::endl;
		exit(EXIT_FAILURE);
	}

	if (listen(_fd, 3) < 0) //listen for connections
	{
		std::cerr << "Listen failed" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	std::cout << "Server is running on port " << _port << " with password " << _password << std::endl;
}

void Server::closeConnection()
{
	if (this->_fd != -1)
		close(this->_fd);
	std::cout << "Server on port " << _port << " has been closed." << std::endl;
}
		
