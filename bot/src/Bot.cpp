/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfranke <pfranke@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 11:17:01 by pfranke           #+#    #+#             */
/*   Updated: 2026/02/26 15:58:56 by pfranke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Bot.hpp"

void Bot::Log(const std::string &message)
{
	std::cout << "[" << _name << "] " << message << std::endl;
}

Bot::Bot(std::string name) : _bot_fd(-1), _name(name)
{
	Log("Was created.");
}

Bot::~Bot()
{
	Log("Was destroyed.");
}

void Bot::ConnectToServer(int port, const std::string &password)
{
    struct sockaddr_in serv_addr;
    
    _bot_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (_bot_fd < 0) {
        Log("Socket creation error");
        return;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        Log("Invalid address/ Address not supported");
        return;
    }

    if (connect(_bot_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        Log("Connection Failed. Is the server running?");
        return;
    }

    std::string pass_cmd = "PASS " + password + "\r\n";
    std::string nick_cmd = "NICK " + _name + "\r\n";
    std::string user_cmd = "USER " + _name + " 0 * :I am a 42 Bot\r\n";
    
    send(_bot_fd, pass_cmd.c_str(), pass_cmd.length(), 0);
    send(_bot_fd, nick_cmd.c_str(), nick_cmd.length(), 0);
    send(_bot_fd, user_cmd.c_str(), user_cmd.length(), 0);

    Log("Connected and Registered.");
}
void Bot::ConnectToChannel(const std::string &channel_name)
{
	if (_bot_fd >= 0)
	{
		std::string join_cmd = "JOIN " + channel_name + "\r\n";
		send(_bot_fd, join_cmd.c_str(), join_cmd.length(), 0);
		Log("Joined channel: " + channel_name);
	}
}

void Bot::DisconnectFromChannel(const std::string &channel_name)
{
	if (_bot_fd >= 0)
	{
		std::string part_cmd = "PART " + channel_name + "\r\n";
		send(_bot_fd, part_cmd.c_str(), part_cmd.length(), 0);
		Log("Left channel: " + channel_name);
	}
}

void Bot::SendMessage(const std::string &message, const std::string &channel_name)
{
	if (_bot_fd >= 0)
	{
		std::string msg = "PRIVMSG " + channel_name + " :" + message + "\r\n";
		send(_bot_fd, msg.c_str(), msg.length(), 0);
	}
	Log("Sending message: " + message);
	
}

void Bot::LoopEvents()
{
	char buffer[1024];
	ssize_t bytes = recv(_bot_fd, buffer, sizeof(buffer) - 1, 0);
	if (bytes > 0)
	{
		buffer[bytes] = '\0';
		std::string response(buffer);
		if (response.find("quoi") != std::string::npos)
		{
			SendMessage("feur", "#test");
		}
		Log("Received: " + response);
	}
	
}