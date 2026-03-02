/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiroux <pgiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 17:19:58 by pgiroux           #+#    #+#             */
/*   Updated: 2026/02/23 13:45:42 by pgiroux          ###   ########.fr       */
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

		bool					_hasPwd;
		bool					_isTopicSet;
		bool					_modeI;
		bool					_modeT;
		bool					_modeK;
		bool					_modeL;




	public :
		Channel(std::string name, int fd);

		std::string				getChannelName(){return (this->_name);};
		std::string 			getTopic();
		std::string				getPwd(){return (this->_pwd);};
		std::string				getClientList();
		std::string				getModes();
		int						getFdCreator() {return (this->_fdCreator);};
		std::vector<int> &		getFdOperators(){return (this->_fdOperators);};

		size_t 					getNbUser(){return (this->_nbUser);};
		size_t 					getMaxUser(){return (this->_maxUser);};
		bool 					isClient(int fd);
		bool					isClient(std::string nickname);
		bool 					isTopicSet(){return (this->_isTopicSet);};
		bool 					isEmpty();
		bool 					isOperator(int fd);
		bool 					isInvited(int fd);
		bool					hasModeI();
		bool					hasModeT();
		bool					hasModeK();
		bool					hasModeL();

		void 					setChannelName(std::string name);
		void 					setTopic(std::string topic);
		void 					setPwd(std::string pwd);
		void 					setMaxUser(size_t nb);	
		void					setModeI(bool boolean);
	    void					setModeT(bool boolean);
	    void					setModeK(bool boolean);
		void					setModeL(bool boolean);
		
		void 					inviteClient(int fd);
		void 					part(int fd);
		void 					delUser(std::string name);
		void					decrementUser();
		void 					addOperator(int fd);
		void 					delOperator(int fd);
		void 					addClient(Client *client);
		void					broadcast(std::string message, int fd);

		~Channel();
};

#endif