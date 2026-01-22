/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiroux <pgiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:44:42 by pgiroux           #+#    #+#             */
/*   Updated: 2026/01/22 17:45:47 by pgiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector> //-> for vector
#include <sys/socket.h> //-> for socket()
#include <sys/types.h> //-> for socket()
#include <netinet/in.h> //-> for sockaddr_in
#include <fcntl.h> //-> for fcntl()
#include <unistd.h> //-> for close()
#include <arpa/inet.h> //-> for inet_ntoa()
#include <sys/select.h> //-> for select()
#include <csignal> //-> for signal()

class Server
{
private:
	int					_port;
	std::string 		_password;
	struct sockaddr_in 	_addr;
	int					_fd;
	static bool 		_Signal;
	
public:
	Server();
	Server(const Server& c);
	void init_server(int port, std::string password);
	static void Signal_handler(int signum);
	void closeFds();
	void run();
	Server&operator=(const Server &rhs);
	~Server();
};


