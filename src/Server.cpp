/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiroux <pgiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:44:56 by pgiroux           #+#    #+#             */
/*   Updated: 2026/02/19 13:49:16 by pgiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"
#include "../include/Colors.hpp"

bool Server::_Signal = false;

void Server::signalHandler(int signum)
{
	if (signum == SIGINT)
		_Signal = true ;
	std::cout << "Signal received" << std::endl;
}
Server::Server() : _fd(-1), _clientFd(-1)
{
	this->_epoll.fd = -1;
	this->_epoll.nb_events = 0;
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
	struct sigaction sa = {};
	sa.sa_handler = signalHandler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL))
		clearData();
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
	clearData();
}

void Server::sendMessage(std::string const &message, int fd)
{
	std::string tmp = message;
	if (tmp.size() > 510)
		tmp = tmp.substr(0, 510) + "\r\n";
	send(fd, tmp.c_str(), tmp.size(), 0);
}

void Server::closeFds()
{
	if (this->_fd == -1)
		close(this->_fd);
}

void Server::removeChannel(std::string channelName)
{
	if (this->_channels.erase(channelName) == 0)
        std::cout << "Channel " << channelName << " doesn't exist.\n";
}

Client *Server::getClient(int fd)
{
	for (std::map<int, Client *>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
	{
		if (it->first == fd)
			return (it->second);
	}
	return (NULL);
}

Client *Server::getClient(std::string name)
{
	for (std::map<int, Client *>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
	{
		if (it->second->getNickname() == name)
			return (it->second);
	}
	return (NULL);
}

Channel *Server::getChannel(std::string name)
{
	for (std::map<std::string, Channel *>::iterator it = this->_channels.begin(); it != this->_channels.end(); it++)
	{
		if (it->first == name)
			return (it->second);
	}
	return (NULL);
}
Channel *Server::addChannel(std::string channelName, Client * client)
{
	Channel *channel = new Channel(channelName, client->getFd());
	channel->addOperator(client->getFd());
	channel->addClient(client);
	this->_channels[channelName] = channel;
	client->addChannel(channel);
	return (channel);
}

Server::~Server()
{
	
}

void	Server::clearData()
{
	for (std::map<int, Client*>::iterator it = this->_clients.begin(); it != this->_clients.end(); ++it)
	{
		close(it->first);
		delete it->second;
	}
	this->_clients.clear();
	for (std::map<std::string, Channel *>::iterator it = this->_channels.begin(); it != this->_channels.end(); it++)
		delete it->second;
	if (this->_fd > -1)
	{
		shutdown(this->_fd, SHUT_RDWR);
		close(this->_fd);
		this->_fd = -1;
	}
	if (this->_epoll.fd > -1)
	{
		close(this->_epoll.fd);
		this->_epoll.fd = -1;
	}
}
