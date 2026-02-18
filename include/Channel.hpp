/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiroux <pgiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 17:19:58 by pgiroux           #+#    #+#             */
/*   Updated: 2026/02/18 10:27:19 by pgiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CHANEL_HPP
#	define __CHANEL_HPP

#include "Server.hpp"
#include "Other.hpp"

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
		bool					_modeI;
		bool					_modeT;
		bool					_modeK;
		bool					_modeO;
		bool					_modeL;




	public :
		Channel(std::string name, int fd);
		~Channel();
		std::string				getChannelName(){return (this->_name);};
		std::string 			getTopic();
		std::string				getPwd(){return (this->_pwd);};
		std::string				getClientList();
		std::string				getModes();
		int						getFdCreator() {return (this->_fdCreator);};
		std::vector<int> &		getFdOperators(){return (this->_fdOperators);};

		size_t 					getNbUser(){return (this->_nbUser);};
		size_t 					getMaxUser(){return (this->_maxUser);};
		bool 					hasUserLimit(){return (this->_hasUserLimit);};
		bool 					getHasPwd();
		bool 					isClient(int fd);
		bool					isClient(std::string nickname);
		bool					isInviteOnly(){return (this->_inviteOnly);};
		bool 					isTopicSet(){return (this->_isTopicSet);};
		bool					isTopicRestricted(){return (this->_topicRestricted);};
		bool 					isEmpty();
		bool 					isOperator(int fd);
		bool 					isInvited(int fd);
		bool					hasModeI();
		bool					hasModeT();
		bool					hasModeK();
		bool					hasModeO();
		bool					hasModeL();
		
	
	


		void 					setChannelName(std::string name);
		void 					setTopic(std::string topic);
		void 					setPwd(std::string pwd);
		void 					setMaxUser(size_t nb);	
		void 					setHasUserLimit(bool boolean);
		void 					setInviteOnly(bool boolean);
		void 					setTopicRestricted(bool boolean);
		void					setModeI(bool boolean);
	    void					setModeT(bool boolean);
	    void					setModeK(bool boolean);
	    void					setModeO(bool boolean);
		void					setModeL(bool boolean);
		void 					inviteClient(int fd);
		void 					part(int fd);
		void 					delUser(std::string name);
		void 					addOperator(int fd);
		void 					delOperator(int fd);
		void 					addClient(Client *client);

};

#endif