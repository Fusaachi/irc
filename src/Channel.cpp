
#include "Server.hpp"

Channel::Channel(std::string name, int fd) : _name(name), _topic(""), _pwd(""), _fd(fd), _inviteOnly(false), _topicRestricted(false), _hasUserLimit(false), _hasPwd(false),_nbUser(1), _maxUser(1), _modeT(false)
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
		if (*it = fd)
			return (true);
	}
	return false;
}

bool Channel::isInvited(int fd)
{
	for (std::vector<int>::iterator it = this->_fdInvited.begin(); it != this->_fdInvited.end(); it++)
	{
		if (*it = fd)
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

void Channel::part(int fd)
{
	for(std::map<int, Client *>::iterator it = this->_fdClients.begin(); it != this->_fdClients.end(); it++ )
	{
		if (it->first == fd)
		{
			it = this->_fdClients.erase(it);
			break;
		}
	}
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
}

void Channel::kick(std::string name)
{
	for(std::map<int, Client *>::iterator it = this->_fdClients.begin(); it != this->_fdClients.end(); it++ )
	{
		if (it->second->getNickname() == name)
		{
			it = this->_fdClients.erase(it);
			break;
		}
	}
	
}


