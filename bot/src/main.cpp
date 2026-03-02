/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfranke <pfranke@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 17:16:43 by pfranke           #+#    #+#             */
/*   Updated: 2026/03/02 16:27:16 by pfranke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Bot.hpp"

static volatile sig_atomic_t g_signal_received = 0;

void signal_handler(int signal)
{
	g_signal_received = signal;
}
int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		std::cerr << "Usage: " << argv[0] << " <port> <password>" << std::endl;
		return 1;
	}
	
	signal(SIGINT, signal_handler);	
	Bot bot("QuoicouBot");
	bot.ConnectToServer(std::atoi(argv[1]), argv[2]);
	bot.ConnectToChannel("#feur");
	while (g_signal_received == 0) 
		bot.LoopEvents();
}