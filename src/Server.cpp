/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiroux <pgiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:44:56 by pgiroux           #+#    #+#             */
/*   Updated: 2026/02/09 14:57:54 by pgiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"
#include "../include/Colors.hpp"

bool Server::_Signal = false;

void Server::signalHandler(int signum)
{
	(void) signum;
	Server::_Signal = true;
	std::cout << "Signal received" << std::endl;
}
Server::Server() : _fd(0)
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

void Server::initServer(int port, std::string password)
{
	this->_port = port;
	this->_password = password;
	// STEP 1 Create a socket - socket()
	this->_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_fd == -1)
		throw std::runtime_error("[Server] Error, Invalid socket");
	int opl = 1;
	if (setsockopt(this->_fd, SOL_SOCKET,SO_REUSEADDR, &opl,sizeof(opl)) == -1) /* allows a server to restart immediately on the same port, even if that port is still considered "occupied" by the system. */
		throw std::runtime_error ("[Server] Error, failed to set option (SO_REUSEADDR) on socket");
	if (fcntl(this->_fd, F_SETFL, O_NONBLOCK) == -1) /* When possible, the file is opened in nonblocking mode.*/
		throw std::runtime_error ("[Server] Error, failed to set option (O_NONBLOCK) on socket");

	// STEP 2 Bind the socket - bind()
	memset(&this->_addr, 0, sizeof this->_addr);
	this->_addr = sockaddr_in();
	this->_addr.sin_family = AF_INET;
	this->_addr.sin_port = htons(_port);
	this->_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(this->_fd, (struct sockaddr *)&this->_addr, sizeof(this->_addr)) == -1) // assign a specific address and port to a socket
		throw std::runtime_error("[Server] Error, failed to bind socket");


	// STEP 3 Listen on the socket - listen()
	if (listen(this->_fd, MAX_EVENTS) == - 1)
		throw std::runtime_error("[Server] Error, listening on socket");

	std::cout << GREEN << "[Server] Server <" <<  this->_fd << "> Connected" << RESET << std::endl;
	std::cout << "[Server] Waiting to accept a connection..." << std::endl;
}

void Server::run()
{
	signal(SIGINT, Server::signalHandler);
	signal(SIGQUIT, Server::signalHandler);

	int nb_events = 0;
	this->_epoll.fd = epoll_create1(0);
	if (this->_epoll.fd == -1)
		throw std::runtime_error("[Server] Error, epoll_create1 failed");
	this->_epoll.event.events = EPOLLIN;
	this->_epoll.event.data.fd = this->_fd;
	if (epoll_ctl(this->_epoll.fd, EPOLL_CTL_ADD, this->_fd, &this->_epoll.event) < 0)
		throw std::runtime_error("[Server] Error, epoll_stl ADD server failed");
	while(Server::_Signal == false)
	{
		nb_events = epoll_wait(this->_epoll.fd, this->_epoll.events, MAX_EVENTS, -1);
		if (nb_events == -1 && Server::_Signal == false)
			throw std::runtime_error ("[Server] Error, epoll wait failed");
		for (int i = 0 ; i < nb_events; i++)
		{
			if (this->_epoll.events[i].data.fd ==  this->_fd)
				acceptNewClient();
			else
				receiveData(this->_epoll.events[i].data.fd);
		}
		
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
