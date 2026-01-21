/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiroux <pgiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:44:51 by pgiroux           #+#    #+#             */
/*   Updated: 2026/01/20 16:50:36 by pgiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"


void parsing(int port, std::string password)
{
	if (port < 1024 || port > 49151)
		throw std::invalid_argument("Error, the port must be between 1024 and 49151");
	if (password.length() < 1)
		throw std::invalid_argument("Error, password must contain at least one char");
}

int main (int argc, char **argv)
{
	try 
	{
		if (argc != 3)
			throw std::invalid_argument("Error, the executable file must be launched like this : ./ircserv [port] [password]");
		int port = atoi(argv[1]);
		std::string password = argv[2];
		parsing(port, password);
		Server server(port, password);
		server.init_server();
	// STEP 4 Accept a connection - accept(), connect()

	// STEP 5 Send and receive data - recv(), send(), recvfrom(), sendto()
	// STEP 6 Disconnect - closesocket()
	//inet_pton(AF_INET, );
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return (0);
}

