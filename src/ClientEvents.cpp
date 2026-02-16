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
	std::cout << RED << "[Server] Client <" << fd << "> Disconnected" << RESET << std::endl;
	epoll_ctl(this->_epoll.fd, EPOLL_CTL_DEL, fd, &this->_epoll.event);
	if (fd > -1)
		close (fd);
	for (std::map<int, Client *>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
	{
		if (it->first == fd)
		{
			close(it->first);
			this->_clients.erase(it);
		}

	}

	for(std::vector<int>::iterator it = this->_fds.begin(); it != this->_fds.end(); it++)
	{
		if (*it == fd)
		{
			this->_fds.erase(it);
			break;
		}
	}
}

void	Server::receiveData(int fd)
{
	char buff[1024];
	memset(buff, 0, sizeof(buff));
	ssize_t bytes = recv(fd, buff, sizeof(buff) - 1, 0);
	
	if (bytes <= 0)
		clientDisconnect(fd);
	else 
	{
		std::string new_data(buff, bytes);
		this->_clients[fd]->appendData(new_data);
		size_t i = 0;
		
		while((i = this->_clients[fd]->getData().find("\r\n")) != std::string::npos)
		{
			std::string command = this->_clients[fd]->getData().substr(0, i + 2);
			std::vector<std::pair<std::string,std::string> > commands =  this->_clients[fd]->splitBuffer(command);
		}
	}
}


