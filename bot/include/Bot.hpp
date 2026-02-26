/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfranke <pfranke@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 11:16:41 by pfranke           #+#    #+#             */
/*   Updated: 2026/02/26 15:58:15 by pfranke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
#define BOT_HPP

#include "../../include/Other.hpp"
class Bot
{
	private:
		int _bot_fd;
		const std::string _name;
		void Log(const std::string &_message);
	public:
		Bot(std::string name);
		~Bot();
		void ConnectToServer(int port, const std::string &password);
		void ConnectToChannel(const std::string &channel_name);
		void DisconnectFromChannel(const std::string &channel_name);
		void SendMessage(const std::string &message, const std::string &channel_name);
		void LoopEvents();
};

void Loop();

#endif