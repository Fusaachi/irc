/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiroux <pgiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:44:51 by pgiroux           #+#    #+#             */
/*   Updated: 2026/03/02 15:50:17 by pgiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"
#include "../include/Colors.hpp"


void parsing(int port, std::string password)
{
	if (port < 1024 || port > 49151)
		throw std::invalid_argument("Error, the port must be between 1024 and 49151");
	if (password.length() < 1)
		throw std::invalid_argument("Error, password must contain at least one char");
}

int main (int argc, char **argv)
{
	Server server;
	try 
	{
		if (argc != 3)
			throw std::invalid_argument("Error, the executable file must be launched like this : ./ircserv [port] [password]");
		int port = atoi(argv[1]);
		std::string password = argv[2];
		parsing(port, password);
		std::cout << BOLDGREEN << "Welcome to Irc ! Port is: " << port << " and password is: " << password << RESET << std::endl;
		std::cout << ORANGE << "Initializing server..." << RESET << std::endl;
		server.initServer(port, password);
		server.run();
	}
	catch(const std::exception& e)
	{
		server.closeFds();
		std::cerr << e.what() << '\n';
	}
	return (0);
}

