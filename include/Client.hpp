/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiroux <pgiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:44:45 by pgiroux           #+#    #+#             */
/*   Updated: 2026/02/18 13:21:49 by pgiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CLIENT_HPP
# define	__CLIENT_HPP

#include "Server.hpp"
#include "Other.hpp"

class Server;
class Channel;

class Client
{
	private:
		std::string		_nickname;
		std::string		_username;
		std::string		_realname;
		std::string		_message;
		std::string		_data;
		std::string		_hostname;
		std::string		_clientAddr;
		
		int				_fd;
		
		bool			_hasPwd;
		bool			_hasNickname;
		bool			_hasUsername;
		bool			_register;
		bool			_operator;
		bool			_hasMaxChannel;

		std::vector<Channel *>	_channels;

	public:
		Client(int fd);
		Client(const Client &c);
		Client &operator=(const Client &rhs);
		
		
		std::string		getNickname(){return _nickname;};
		std::string		getUsername(){return _username;};
		std::string		getRealname(){return _realname;};
		std::string		getMessage(){return _message;};
		std::string		getHostname(){return _hostname;};
		std::string		getClientAddr(){return _clientAddr;};
		
		int				getFd(){return _fd;};
		int				getNbChannel();
		
		bool			getHasPassword(){return _hasPwd;};
		bool			getHasNickname(){return _hasNickname;};
		bool			getHasUsername(){return _hasUsername;};
		bool			isRegister(){return _register;};
		bool			isOperator(){return _operator;};
		bool			hasMaxChannel() {return	_operator;};

		void			setNickname(std::string const &nickname);
		void			setUsername(std::string const &username);
		void			setRealname(std::string const &realname);
		void			setMessage(std::string const &message);
		void			setHostname(std::string const &hostname);
		void			setClientAddr(std::string const &clientAddr);
		void			setFd(int fd);
		void			setData(const std::string &data);
		void			setHasPassword(bool boolean);
		void			setHasUsername(bool boolean);
		void			setHasNickname(bool boolean);
		void			setIsRegister(bool boolean);
		void			setIsOperator(bool boolean);
		void			setHasMaxChannel(bool boolean);

		void 			appendData(std::string new_data);
		void			addChannel(Channel *channel);
		std::string 	getData(){return this->_data;};
		std::vector<std::pair<std::string , std::string> > splitBuffer(std::string const &buffer);
		std::pair<std::string, std::string> pair(std::string command, std::string args);
		~Client();
};

#endif

