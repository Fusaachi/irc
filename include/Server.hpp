/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiroux <pgiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:44:42 by pgiroux           #+#    #+#             */
/*   Updated: 2026/02/12 16:15:50 by pgiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SERVER_HPP
# define	__SERVER_HPP

#include "Client.hpp"
#include "Channel.hpp"
#include "Colors.hpp"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <sys/socket.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <fcntl.h> 
#include <unistd.h> 
#include <arpa/inet.h> 
#include <poll.h> 
#include <sys/epoll.h>
#include <csignal>
#include <map>
# define MAX_EVENTS  10

typedef struct s_epoll
{
	int					fd;
	int					nb_events;
	struct epoll_event	event;
	struct epoll_event	events[MAX_EVENTS];
	
}t_epoll;

void send_message(Client *client, std::string const &message);

class Client;

class Server
{
private:
	int						_port;
	std::string 			_password;
	struct sockaddr_in 		_addr;
	int						_fd;
	int						_clientFd;
	static bool 			_Signal;
	
	t_epoll					_epoll;

	std::map<int, Client*> 	_clients;
	std::vector<int>		_fds;
	std::map<std::string, Channel *>	_channels;
	
public:
	Server();
	Server(const Server& c);
	void		initServer(int port, std::string password);
	static void	signalHandler(int signum);
	void		acceptNewClient();
	void		receiveData(int fd);
	void		clientDisconnect(int fd);
	void		closeFds();
	void 		run();

	Client *getClient(int fd){return this->_clients[fd];};
	std::map<int, Client*> &getClients(){return this->_clients;};
	Channel *getChannel(std::string name){return this->_channels[name];};
	std::map<std::string, Channel*> &getChannels(){return this->_channels;};
	
	std::string getPassword() {return _password;};
	Server&operator=(const Server &rhs);
	~Server();
};


#endif