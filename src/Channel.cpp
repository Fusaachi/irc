
#include "Server.hpp"

Channel::Channel(std::string name, int fd) : _name(name), _fd(fd)
{

}

Channel::~Channel()
{

}

bool Channel::is_client(int fd)
{

	for(std::map<int, Client *>::iterator it = this->_fdClients.begin(); it != this->_fdClients.end(); it++ )
	{
		if (it->first == fd)
			return (true);
	}
	return (false);
}
