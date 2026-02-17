/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiroux <pgiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 17:22:56 by pgiroux           #+#    #+#             */
/*   Updated: 2026/02/17 11:13:01 by pgiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/Server.hpp"

Channel::Channel(std::string name, int fd) : _name(name), _topic(""), _pwd(""), _fdCreator(fd), _nbUser(1), _maxUser(1), _hasUserLimit(false), _hasPwd(false), _inviteOnly(false), _topicRestricted(false),  _modeT(false)
{

}

Channel::~Channel()
{

}

bool Channel::isClient(int fd)
{
	for(std::map<int, Client *>::iterator it = this->_fdClients.begin(); it != this->_fdClients.end(); it++)
	{
		if (it->first == fd)
			return (true);
	}
	return (false);
}

bool Channel::isClient(std::string nickname)
{
	for(std::map<int, Client *>::iterator it = this->_fdClients.begin(); it != this->_fdClients.end(); it++)
	{
		if (it->second->getNickname() == nickname)
			return (true);
	}
	return (false);
}

bool Channel::getHasPwd()
{
	if (this->_hasPwd == true)
		return (true);
	return (false);
}

std::string Channel::getTopic()
{
	if (this->_isTopicSet == true)
		return this->_topic;
	return NULL;
}

void Channel::setChannelName(std::string name) 
{
	this->_name = name;
}


void Channel::setTopic(std::string topic)
{
	this->_topic = topic;
	this->_isTopicSet = true;
}

void Channel::setPwd(std::string pwd)
{
	this->_pwd = pwd;
	this->_hasPwd = true;
}

void Channel::setInviteOnly(bool boolean)
{
	this->_inviteOnly = boolean;
}

void Channel::setTopicRestricted(bool boolean)
{
	this->_topicRestricted = boolean;
}
void	Channel::setMaxUser(size_t nb)
{
	this->_maxUser = nb;
}

void	Channel::setHasUserLimit(bool boolean)
{
	this->_hasUserLimit = boolean;
}

bool	Channel::isEmpty()
{
	if (this->_nbUser == 0)
		return true;
	return false;
}

bool	Channel::isOperator(int fd)
{
	for (std::vector<int>::iterator it = this->_fdOperators.begin(); it != this->_fdOperators.end(); it++)
	{
		if (*it == fd)
			return (true);
	}
	return false;
}

bool Channel::isInvited(int fd)
{
	for (std::vector<int>::iterator it = this->_fdInvited.begin(); it != this->_fdInvited.end(); it++)
	{
		if (*it == fd)
			return (true);
	}
	return false;
}

bool Channel::isModeT()
{
	if (this->_modeT == true)
		return (true);
	return(false);
}

void Channel::inviteClient(int fd)
{
	if (this->isInvited(fd))
		this->_fdInvited.push_back(fd);
	this->_nbUser++;
}

void Channel::part(int fd)
{
	if (this->_fdClients.erase(fd) == 0)
        std::cout << "Fd client " << fd << " doesn't exist.\n";
	if (isOperator(fd))
	{
		for(std::vector<int>::iterator it = this->_fdOperators.begin(); it != this->_fdOperators.end(); it++ )
		{
			if (*it == fd)
			{
				it = this->_fdOperators.erase(it);
				break;
			}
		}
	}
	
	if (isInvited(fd))
	{
		for(std::vector<int>::iterator it = this->_fdInvited.begin(); it != this->_fdInvited.end(); it++ )
		{
			if (*it == fd)
			{
				it = this->_fdInvited.erase(it);
				break;
			}
		}
	}
	this->_nbUser--;
}

void Channel::delUser(std::string name)
{
	for(std::map<int, Client *>::iterator it = this->_fdClients.begin(); it != this->_fdClients.end(); it++ )
	{
		if (it->second->getNickname() == name)
		{
			if (isOperator(it->first))
			{
				for (std::vector<int>::iterator it2 = this->_fdOperators.begin(); it2 != this->_fdOperators.end(); it2++)
				{
					if (*it2 == it->first)
					{
						it2 = this->_fdOperators.erase(it2);
						break;
					}
				}
			}
			this->_fdClients.erase(it);
			break;
		}
	}
	this->_nbUser--;
}

void Channel::addOperator(int fd)
{
	if (this->isOperator(fd) == false)
		this->_fdOperators.push_back(fd);
}

void Channel::delOperator(int fd)
{
	if (this->isOperator(fd) == true)
	{
		for (std::vector<int>::iterator it = this->_fdOperators.begin(); it != this->_fdOperators.end(); it++)
		{
			if (*it == fd)
				it = this->_fdOperators.erase(it);
		}
	}
}

void Channel::addClient(Client *client)
{
	if (this->_fdCreator == client->getFd() || (this->isInvited(client->getFd()) && this->getNbUser() < this->getMaxUser()))
	{
		this->_fdClients.insert(std::make_pair(client->getFd(), client));
		this->_nbUser++;
	}	
}