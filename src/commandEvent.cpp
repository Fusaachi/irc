/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandEvent.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiroux <pgiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 17:23:09 by pgiroux           #+#    #+#             */
/*   Updated: 2026/02/25 17:26:57 by pgiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

Commands::Commands(){}

void Commands::executeCommands(Server *server, int fd, std::pair<std::string, std::string> command)
{
	std::string tableCommands[12] = {"INVITE", "JOIN", "KICK", "MODE", "NICK", "PART", "PASS", "PING", "PRIVMSG", "QUIT", "TOPIC", "USER"};
	static void (Commands::*table[12])(Server*, int, std::string) = {&Commands::INVITE, &Commands::JOIN, &Commands::KICK, &Commands::MODE, &Commands::NICK, &Commands::PART, &Commands::PASS, &Commands::PING, &Commands::PRIVMSG, &Commands::QUIT, &Commands::TOPIC, &Commands::USER};

	for (int i = 0; i < 12; i++)
	{
		std::cout << "command = " << command.first << "arg = " << command.second << std::endl;
		if (tableCommands[i] == command.first)
		{
			(this->*table[i])(server, fd, command.second);
			return;
		}
	}

 	std::cout << RED << "[Client][Error] Command doesn't exist" << RESET << std::endl;
}