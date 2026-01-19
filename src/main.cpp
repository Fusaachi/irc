#include "Server.hpp"

void parsing(int port, std::string password)
{
	if (port < 1024 && port > 49151)
		throw std::invalid_argument("Error, the port must be between 1024 and 49151");
	if (password.length() < 1)
		throw std::invalid_argument("Error, password must contain at least one char");
}

int main (int argc, char **argv)
{
	try 
	{
		if (argc != 3)
			throw std::invalid_argument("Error, need 2 arguments");
		int port = atoi(argv[1]);
		std::string password = argv[2];
		parsing(port, password);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return (0);
}

