/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfranke <pfranke@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 11:17:01 by pfranke           #+#    #+#             */
/*   Updated: 2026/02/27 10:46:08 by pfranke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Bot.hpp"
#include <netinet/tcp.h>

void Bot::Log(const std::string &message)
{
	std::cout << "[" << _name << "] " << message << '\n';
}

Bot::Bot(std::string name) : _bot_fd(-1), _name(name), _channel("")
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

    int flag = 1;
    setsockopt(_bot_fd, IPPROTO_TCP, TCP_NODELAY, &flag, sizeof(int));

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
    std::string user_cmd = "USER " + _name + "\r\n";
    
    send(_bot_fd, pass_cmd.c_str(), pass_cmd.length(), 0);
    send(_bot_fd, nick_cmd.c_str(), nick_cmd.length(), 0);
    send(_bot_fd, user_cmd.c_str(), user_cmd.length(), 0);

    Log("Connected and Registered.");
}
void Bot::ConnectToChannel(const std::string &channel_name)
{
	if (_bot_fd >= 0)
	{
		_channel = channel_name;
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

void Bot::SendRaw(const std::string &message)
{
	if (_bot_fd >= 0)
		send(_bot_fd, message.c_str(), message.length(), 0);
}

void Bot::SendMessage(const std::string &message, const std::string &channel_name)
{
	if (_bot_fd >= 0)
	{
		std::string msg = "PRIVMSG " + channel_name + " :" + message + "\r\n";
		SendRaw(msg);
	}
}

void Bot::HandleMessage(const std::string &line)
{
	if (line.empty())
		return;
	
	if (line.find("PING") == 0)
	{
		size_t pos = line.find(':');
		if (pos != std::string::npos)
		{
			std::string pong = "PONG " + line.substr(pos) + "\r\n";
			SendRaw(pong);
		}
		return;
	}
	
	if (line.find("PRIVMSG") != std::string::npos && !_channel.empty())
	{
		size_t nick_end = line.find('!');
		if (nick_end != std::string::npos)
		{
			std::string sender = line.substr(1, nick_end - 1);
			if (sender == _name)
				return;
		}
		
		size_t msg_pos = line.find(':', 1);
		if (msg_pos != std::string::npos)
		{
			std::string msg = line.substr(msg_pos + 1);
			for (size_t i = 0; i < msg.length(); i++)
				msg[i] = std::tolower(msg[i]);
			
			if (msg.find("quoi") != std::string::npos)
				SendMessage("feur", _channel);
			else if (msg.find("comment") != std::string::npos)
				SendMessage("Dent Cousteau", _channel);
		}
	}
}

void Bot::LoopEvents()
{
	struct pollfd pfd;
	pfd.fd = _bot_fd;
	pfd.events = POLLIN;
	
	int ret = poll(&pfd, 1, 1);
	if (ret <= 0)
		return;
	
	char buffer[4096];
	ssize_t bytes = recv(_bot_fd, buffer, sizeof(buffer) - 1, 0);
	if (bytes <= 0)
		return;
	
	buffer[bytes] = '\0';
	_buffer.append(buffer, bytes);
	
	size_t pos;
	while ((pos = _buffer.find("\r\n")) != std::string::npos)
	{
		HandleMessage(_buffer.substr(0, pos));
		_buffer.erase(0, pos + 2);
	}
	
	if (_buffer.size() > 8192)
		_buffer.clear();
}