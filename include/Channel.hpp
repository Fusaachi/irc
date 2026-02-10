#ifndef __CHANEL_HPP
#	define __CHANEL_HPP

#include "Server.hpp"

class Client;

class Channel
{
	private :
		std::string				_name;
		std::string				_topic;

		std::map<int,Client *>	_fdClients;
		std::vector<int>		_fdOperators;
		std::vector<int>		_fdInvited;

		bool					_inviteOnly;
		bool					_topicRestricted;
		bool					_hasUserLimit;
		size_t					_userLimits;
};

#endif