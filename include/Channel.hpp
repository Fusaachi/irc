#ifndef __CHANEL_HPP
#	define __CHANEL_HPP

#include "Server.hpp"

class Client;

class Channel
{
	private :
		std::string				_name;
		std::string				_topic;
		std::string				_pwd;
		int 					_fd;

		std::map<int, Client *>	_fdClients;
		std::vector<int>		_fdOperators;
		std::vector<int>		_fdInvited;

		bool					_inviteOnly;
		bool					_topicRestricted;
		bool					_hasUserLimit;
		size_t					_userLimits;

	public :
		Channel(std::string name, int fd);
		~Channel();
		std::string getChannelName(){return (this->_name);};
		std::string getTopic(){return (this->_topic);};
		std::string getPwd(){return (this->_pwd);};

		bool is_client(int fd);
};

#endif