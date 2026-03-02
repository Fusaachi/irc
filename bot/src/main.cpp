/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfranke <pfranke@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 17:16:43 by pfranke           #+#    #+#             */
/*   Updated: 2026/03/02 16:23:50 by pfranke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Bot.hpp"

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cerr << "Usage: " << argv[0] << " <port> <password>" << std::endl;
		return 1;
	}
	
	Bot bot("QuoicouBot");
	bot.ConnectToServer(std::atoi(argv[1]), argv[2]);
	bot.ConnectToChannel("#feur");
	while (true) 
		bot.LoopEvents();
}