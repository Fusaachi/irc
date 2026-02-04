#include "../include/Server.hpp"

void Server::acceptNewClient()
{
	struct sockaddr_in client_addr;
	socklen_t len  = sizeof(client_addr);
	struct epoll_event newPoll = epoll_event();
	int client_fd = accept(this->_fd, (struct sockaddr*)&client_addr, &len);
	if (client_fd == -1)
	{
		std::cout << "[Server] accept() failed" << std::endl;
		return;
	}
	newPoll.events = EPOLLIN | EPOLLRDHUP;
	newPoll.data.fd  = client_fd;

	Client client(client_fd);
	this->_clients.push_back(client);
	this->_fds.push_back(client_fd);
	std::cout << "[Server] Accepted new connection on client socket <" << client_fd <<  ">" << std::endl;
}

void Server::clientDisconnect(int fd)
{
	epoll_ctl(this->_epoll.fd, EPOLL_CTL_DEL, fd, &this->_epoll.event);
	if (fd > -1)
		close (fd);
	for (std::vector<int>::iterator it = this->_fds.begin(); it != this->_fds.end(); it++)
	{
		if (*it == fd)
			close(*it);
	}
	for (size_t i = 0; i < sizeof(_clients); i++)
	{
		if (this->_clients[i].getFd() == fd)
			this->_clients.erase(this->_clients.begin() + i);
	}
}

void	Server::receiveData(int fd)
{
	char buff[1024];
	memset(buff, 0, sizeof(buff));
	
	ssize_t bytes = recv(fd, buff, sizeof(buff) - 1, 0);
	if (bytes <= 0)
	{
		std::cout << RED << "[Server] Client <" << fd << "> Disconnected" << RESET << std::endl;
		clientDisconnect(fd);
	}
	else 
	{
		buff[bytes] = '\0';
		std::cout << YELLOW << "Client < " << fd << "> Data: " << RESET << buff; 
	}
}


