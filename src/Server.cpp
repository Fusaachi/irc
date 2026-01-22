/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiroux <pgiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:44:56 by pgiroux           #+#    #+#             */
/*   Updated: 2026/01/22 17:45:40 by pgiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"
#include "../include/Colors.hpp"

bool Server::_Signal = false;

void Server::Signal_handler(int signum)
{
	(void) signum;
	Server::_Signal = true;
	std::cout << "Signal received" << std::endl;
}
Server::Server() : _fd(0)
{

}

Server::Server(const Server& c) : _port(c._port), _password(c._password)
{

}

Server &Server::operator=(const Server & rhs)
{
	if (this != &rhs)
		*this = rhs;
	return (*this);
}

void Server::init_server(int port, std::string password)
{
	this->_port = port;
	this->_password = password;
	// STEP 1 Create a socket - socket()
	this->_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_fd == -1)
		throw std::runtime_error("Error, Invalid socket");
	
	int opl = 1;
	if (setsockopt(this->_fd, SOL_SOCKET,SO_REUSEADDR, &opl,sizeof(opl)) == -1) /* allows a server to restart immediately on the same port, even if that port is still considered "occupied" by the system. */
		throw std::runtime_error ("Error, failed to set option (SO_REUSEADDR) on socket");
	if (fcntl(this->_fd, F_SETFL, O_NONBLOCK) == -1) /* When possible, the file is opened in nonblocking mode.*/
		throw std::runtime_error ("Error, failed to set option (O_NONBLOCK) on socket");

	// STEP 2 Bind the socket - bind()
	memset(&this->_addr,0, sizeof this->_addr);
	this->_addr = sockaddr_in();
	this->_addr.sin_family = AF_INET;
	this->_addr.sin_port = htons(_port);
	this->_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(this->_fd, (struct sockaddr *)&this->_addr, sizeof(this->_addr)) == -1)
		throw std::runtime_error("Error, failed to bind socket");


	// STEP 3 Listen on the socket - listen()
	if (listen(this->_fd, 10) == - 1)
		throw std::runtime_error("Error, listening on socket");

	std::cout << GREEN << "Server <" <<  this->_fd << "> Connected" << RESET << std::endl;
	std::cout << "Waiting to accept a connection...\n";
}

void Server::run()
{
	int status = 0;
	signal(SIGINT, Server::Signal_handler);
	signal(SIGQUIT, Server::Signal_handler);
	struct timeval time;
	fd_set all_sockets; // Ensemble de toutes les sockets du serveur
	fd_set read_fds; // Ensemble temporaire pour select()
	int fd_max = 0; // Descripteur de la plus grande socket
	FD_ZERO(&all_sockets);
	FD_ZERO(&read_fds);
	FD_SET(this->_fd, &all_sockets);
	fd_max = this->_fd;

	while(Server::_Signal == false)
	{
		read_fds = all_sockets;
		time.tv_sec = 2;
		time.tv_usec = 0;
		status  = select(fd_max + 1, &read_fds, NULL, NULL, &time);
		if (status == -1)
			throw std::runtime_error("[Server] Select error");
		else if (status == 0)
		{
			std::cout <<"[Server] Waiting... " << std::endl;
			continue;
		}
		 for (int i = 0; i <= fd_max; i++) {
        	if (FD_ISSET(i, &read_fds) != 1) {
                // Le fd i n'est pas une socket à surveiller
                // on s'arrête là et on continue la boucle
                continue ;
            }
		std::cout <<"[" << i << "] Ready for I/O operation\n"<< std::endl;
            // La socket est prête à être lue !
        if (i == this->_fd) {
                // La socket est notre socket serveur qui écoute le port
				std::cout << "o";
               // accept_new_connection(server_socket, &all_sockets, &fd_max);
            }
            else {
                // La socket est une socket client, on va la lire
				std::cout<< "no";
                //read_data_from_socket(i, &all_sockets, fd_max, server_socket);
            }
	}
}
}

void Server::closeFds()
{
	if (this->_fd == -1)
		close(this->_fd);
}
Server::~Server()
{
	
}
