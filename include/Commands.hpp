/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiroux <pgiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 17:21:30 by pgiroux           #+#    #+#             */
/*   Updated: 2026/02/18 13:01:48 by pgiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __COMMANDS_HPP
 #define __COMMANDS_HPP

#include "Other.hpp"

class Server;

class Commands
{
	private :

		void INVITE(Server *server, int fd, std::string user);
		void JOIN(Server *server, int fd, std::string user);
		void KICK(Server *server, int fd, std::string user);
		void MODE(Server *server, int fd, std::string user);
		void NICK(Server *server, int fd, std::string nick);
		void PART(Server *server, int fd, std::string arg);
		void PASS(Server *server, int fd, std::string password);
		void PING(Server *server, int fd, std::string arg);
		void PRIVMSG(Server *server, int fd, std::string user);
		void QUIT(Server *server, int fd, std::string reason);
		void TOPIC(Server *server, int fd, std::string user);
		void USER(Server *server, int fd, std::string user);

	public :
		Commands();
		void executeCommands(Server *server, int fd, std::pair<std::string, std::string> command);
};

std::vector<std::string> get_channel_names(std::string const &arg);

#endif