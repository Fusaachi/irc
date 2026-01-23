/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiroux <pgiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:44:42 by pgiroux           #+#    #+#             */
/*   Updated: 2026/01/23 16:49:51 by pgiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# define MAX_EVENTS  10

typedef struct s_epoll
{
	int					fd;
	int					nb_events;
	struct epoll_event	event;
	struct epoll_event	events[MAX_EVENTS];
	
}t_epoll;

class Client;

class Server
{
private:
	int					_port;
	std::string 		_password;
	struct sockaddr_in 	_addr;
	int					_fd;
	static bool 		_Signal;
	t_epoll				_epoll;
	std::vector<Client> clients;
	
public:
	Server();
	Server(const Server& c);
	void init_server(int port, std::string password);
	static void Signal_handler(int signum);
	void accept_new_client();
	void receive_data(int fd);
	void closeFds();
	void run();
	Server&operator=(const Server &rhs);
	~Server();
};


