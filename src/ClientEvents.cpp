#include "../include/Server.hpp"

void Server::acceptNewClient()
{
	struct sockaddr_in client_addr;
	socklen_t len  = sizeof(client_addr);
	struct epoll_event newPoll = epoll_event();
	this->_clientFd= accept(this->_fd, (struct sockaddr*)&client_addr, &len);
	if (this->_clientFd == -1)
	{
		std::cout << "[Server] accept() failed" << std::endl;
		return;
	}
	newPoll.events = EPOLLIN | EPOLLRDHUP;
	newPoll.data.fd  = this->_clientFd;

	Client *client = new Client(this->_clientFd);
	this->_clients.insert(std::pair<int, Client*>(this->_clientFd, client));
	this->_fds.push_back(this->_clientFd);
	std::cout << "[Server] Accepted new connection on client socket <" << this->_clientFd <<  ">" << std::endl;
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


