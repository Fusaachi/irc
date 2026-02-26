/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfranke <pfranke@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 11:16:41 by pfranke           #+#    #+#             */
/*   Updated: 2026/02/26 11:28:54 by pfranke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
#define BOT_HPP

#include "Server.hpp"
#include <iostream>
#include <string>
#include <cstdlib>

class Bot
{
	private:
		Server *_server;
		const std::string _name;
		void Log(const std::string &_message);
	public:
		Bot(std::string name);
		~Bot();
		void ConnectToServer(const std::string &server, int port, const std::string &password);
		void SendMessage(const std::string &message);
};

void Loop();

#endif