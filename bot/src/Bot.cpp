/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfranke <pfranke@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 11:17:01 by pfranke           #+#    #+#             */
/*   Updated: 2026/02/26 11:37:51 by pfranke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Bot.hpp"
#include "../include/Server.hpp"

void Bot::Log(const std::string &message)
{
	std::cout << "[" << _name << "] " << message << std::endl;
}

Bot::Bot(std::string name) : _name(name), _server(nullptr)
{
	Log("Was created.");
}

Bot::~Bot()
{
	Log("Was destroyed.");
	if (_server)
		delete _server;
}

void Bot::ConnectToServer(const std::string &server, int port, const std::string &password)
{
	Log("Connecting to server " + server + ":" + std::to_string(port) + " with password " + password);
	this->_server = new Server(port, password);
	this->_server->run();
}

void Bot::SendMessage(const std::string &message)
{
	if (_server)
		_server->sendMessage(message);
	Log("Sending message: " + message);
	
}