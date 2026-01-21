/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiroux <pgiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:44:56 by pgiroux           #+#    #+#             */
/*   Updated: 2026/01/21 17:40:57 by pgiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"
#include "../include/Colors.hpp"

bool Server::_Signal = false;

void Server::Signal_handler(int signum)
{
	(void) signum;
	Server::_Signal = true;
	std::cout << "Signal received" << std::endl;
}
Server::Server(int port, std::string password) : _port(port), _password(password)
{

}

Server::Server(const Server& c) : _port(c._port), _password(c._password)
{

}

Server &Server::operator=(const Server & rhs)
{
	if (this != &rhs)
		*this = rhs;
	return (*this);
}

void Server::init_server()
{
	// STEP 1 Create a socket - socket()
	this->_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_fd == -1)
		throw std::runtime_error("Error, Invalid socket");
	
	int opl = 1;
	if (setsockopt(this->_fd, SOL_SOCKET,SO_REUSEADDR, &opl,sizeof(opl)) == -1) /* allows a server to restart immediately on the same port, even if that port is still considered "occupied" by the system. */
		throw std::runtime_error ("Error, failed to set option (SO_REUSEADDR) on socket");
	if (fcntl(this->_fd, F_SETFL, O_NONBLOCK) == -1) /* When possible, the file is opened in nonblocking mode.*/
		throw std::runtime_error ("Error, failed to set option (O_NONBLOCK) on socket");

	// STEP 2 Bind the socket - bind()
	this->_addr = sockaddr_in();
	this->_addr.sin_family = AF_INET;
	this->_addr.sin_port = htons(_port);
	this->_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(this->_fd, (struct sockaddr *)&this->_addr, sizeof(this->_addr)) == -1)
		throw std::runtime_error("Error, failed to bind socket");


	// STEP 3 Listen on the socket - listen()
	if (listen(this->_fd, 10) == - 1)
		throw std::runtime_error("Error, listening on socket");

	std::cout << GREEN << "Server <" <<  this->_fd << "> Connected" << RESET << std::endl;
	std::cout << "Waiting to accept a connection...\n";
}

void Server::run()
{
	signal(SIGINT, Server::Signal_handler);
	signal(SIGQUIT, Server::Signal_handler);
	while(Server::_Signal == false)
	{
		
	}
}

void Server::closeFds()
{
	if (this->_fd == -1)
		close(this->_fd);
}
Server::~Server()
{
	
}
