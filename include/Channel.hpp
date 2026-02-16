#ifndef __CHANEL_HPP
#	define __CHANEL_HPP

#include "Server.hpp"
#include <map>
#include <vector>
#include <iostream>

class Client;

class Channel
{
	private :
		std::string				_name;
		std::string				_topic;
		std::string				_pwd;
		int 					_fdCreator;

		std::map<int, Client *>	_fdClients;
		std::vector<int>		_fdOperators;
		std::vector<int>		_fdInvited;


		size_t					_nbUser;
		size_t					_maxUser;

		bool					_hasUserLimit;
		bool					_hasPwd;
		bool					_inviteOnly;
		bool					_isTopicSet;
		bool					_topicRestricted;
		bool					_modeT;


	public :
		Channel(std::string name, int fd);
		~Channel();
		std::string getChannelName(){return (this->_name);};
		std::string getTopic();
		std::string getPwd(){return (this->_pwd);};
		int			getFdCreator() {return (this->_fdCreator);};
		std::vector<int> &getFdOperators(){return (this->_fdOperators);};

		size_t getNbUser(){return (this->_nbUser);};
		size_t getMaxUser(){return (this->_maxUser);};
		bool hasUserLimit(){return (this->_hasUserLimit);};
		bool getHasPwd();
		bool isClient(int fd);
		bool isInviteOnly(){return (this->_inviteOnly);};
		bool isTopicSet(){return (this->_isTopicSet);};
		bool isTopicRestricted(){return (this->_topicRestricted);};
		bool isEmpty();
		bool isOperator(int fd);
		bool isInvited(int fd);
		bool isModeT();
		
	
	


		void setChannelName(std::string name);
		void setTopic(std::string topic);
		void setPwd(std::string pwd);
		void setMaxUser(size_t nb);	
		void setHasUserLimit(bool boolean);
		void setInviteOnly(bool boolean);
		void setTopicRestricted(bool boolean);

		void inviteClient(int fd);
		void part(int fd);
		void delUser(std::string name);
		void addOperator(int fd);
		void delOperator(int fd);


};

#endif