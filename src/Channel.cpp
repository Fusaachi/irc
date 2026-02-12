
#include "Server.hpp"

Channel::Channel(std::string name, int fd) : _name(name), _topic(""), _pwd(""), _fd(fd), _inviteOnly(false), _topicRestricted(false), _hasUserLimit(false), _hasPwd(false),_nbUser(0), _maxUser(1)
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
