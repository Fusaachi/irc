#include <Server.hpp>


Server::Server(int port, std::string password) : _port(port), _password(password)
{
	// STEP 1 Create a socket - socket()
	this->_fd = socket(AF_INET, SOCK_STREAM, 0);
	if ( this->_fd == -1)
		throw std::runtime_error("Error, Invalid socket");


	// STEP 2 Bind the socket - bind()

	this->_addr = sockaddr_in();
	this->_addr.sin_family = AF_INET;
	this->_addr.sin_port = htons(_port);
	this->_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(this->_fd, (struct sockaddr *)&this->_addr, sizeof(this->_addr)) == -1)
		throw std::runtime_error("failed to bind socket");
	// STEP 3 Listen on the socket - listen()
	// STEP 4 Accept a connection - accept(), connect()
	// STEP 5 Send and receive data - recv(), send(), recvfrom(), sendto()
	// STEP 6 Disconnect - closesocket()
	//inet_pton(AF_INET, );


}

Server::Server(const Server& c)
{
	this->_password = c._password;
	this->_port = c._port;
	this->_addr = c._addr;
	this->_addr.sin_port = c._addr.sin_port;
	this->_addr.sin_family = c._addr.sin_family;
	this->_addr.sin_addr.s_addr = c._addr.sin_addr.s_addr;
}

Server &Server::operator=(const Server & rhs)
{
	if (this != &rhs)
		*this = rhs;
	return (*this);
}

Server::~Server()
{
}
