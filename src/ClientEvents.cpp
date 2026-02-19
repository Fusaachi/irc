/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientEvents.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiroux <pgiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 17:23:06 by pgiroux           #+#    #+#             */
/*   Updated: 2026/02/19 11:05:45 by pgiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

void Server::acceptNewClient()
{
	struct sockaddr_in client_addr;
	socklen_t len  = sizeof(client_addr);
	struct epoll_event newPoll = epoll_event();
	this->_clientFd= accept(this->_fd, (struct sockaddr*)&client_addr, &len);
	if (this->_clientFd == -1)
	{
		std::cout << "[Server] accept() failed" << std::endl;
		return;
	}
	newPoll.events = EPOLLIN | EPOLLRDHUP;
	newPoll.data.fd  = this->_clientFd;

	Client *client = new Client(this->_clientFd);
	this->_clients.insert(std::pair<int, Client*>(this->_clientFd, client));
	this->_fds.push_back(this->_clientFd);
	if (epoll_ctl(this->_epoll.fd, EPOLL_CTL_ADD, this->_clientFd, &newPoll) < 0)
			clearData();
	std::cout << "[Server] Accepted new connection on client socket <" << this->_clientFd <<  ">" << std::endl;
}

void Server::clientDisconnect(int fd)
{
	std::cout << RED << "[Server] Client <" << fd << "> Disconnected" << RESET << std::endl;
	epoll_ctl(this->_epoll.fd, EPOLL_CTL_DEL, fd, &this->_epoll.event);
	std::string nameChannel;
	std::map<int, Client*>::iterator it = this->_clients.find(fd);
	std::vector<Channel*>& channels = it->second->getChannels();
	for (std::vector<Channel*>::iterator itChannel = channels.begin(); itChannel != channels.end(); ++itChannel)
	{
		(*itChannel)->decrementUser();
		if ((*itChannel)->isEmpty())
		{
			nameChannel = (*itChannel)->getChannelName();
			for (std::map<std::string, Channel *>::iterator itChannelServer = this->_channels.begin(); itChannelServer != this->_channels.end();itChannelServer++)
			{
				if (itChannelServer->first == nameChannel)
				{
					delete itChannelServer->second;
					this->_channels.erase(itChannelServer);
					break;
				}
			}
		}
	}
    if (it != this->_clients.end())
    {
        delete it->second;
        this->_clients.erase(it);
    }

	for(std::vector<int>::iterator it = this->_fds.begin(); it != this->_fds.end();)
	{
		if (*it == fd)
			it = this->_fds.erase(it);
		else
			++it;
	}

	if (fd > -1)
		close(fd);
}

void	Server::receiveData(int fd)
{
	char buff[1024];
	memset(buff, 0, sizeof(buff));
	ssize_t bytes = recv(fd, buff, sizeof(buff) - 1, 0);
	
	if (bytes <= 0)
		clientDisconnect(fd);
	else 
	{
		std::string new_data(buff, bytes);
		this->_clients[fd]->appendData(new_data);
		size_t i = 0;
		while((i = this->_clients[fd]->getData().find("\r\n")) != std::string::npos)
		{
			std::string command = this->_clients[fd]->getData().substr(0, i + 2);
			std::vector<std::pair<std::string,std::string> > commands =  this->_clients[fd]->splitBuffer(command);
			for (size_t j = 0; j < commands.size(); j++)
   				_commands.executeCommands(this, fd, commands[j]);
			try
			{
				Client *client = this->_clients.at(fd);
				client->setData(client->getData().substr(i +2));
			}
			catch (const std::out_of_range & oor)
			{
				std::cerr << BOLDRED << "Inexistant client with fd: " << fd << RESET << std::endl;
				break;
			}
		}		
	}
}


