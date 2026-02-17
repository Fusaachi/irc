#include "Server.hpp"
#include "Client.hpp"
#include "errors.hpp"
#include "replies.hpp"
#include "../include/Commands.hpp"

void Commands::INVITE(Server *server, int fd, std::string arg)
{
    std::string channel_name;
    std::string nickname;
    Client *client = server->getClient(fd);
    if (channel_name.empty() || nickname.empty())
    {
        server->sendMessage(ERR_NEEDMOREPARAMS("INVITE"), fd);
        return ;
    }
    Client *client2 = server->getClient(nickname);
    if (!client2)
    {
        server->sendMessage(ERR_NOSUCHNICK(client->getNickname(), nickname), fd);
        return ;
    }
    Channel *channel = server->getChannel(channel_name);
    if (channel)
    {
        if (channel->isClient(nickname))
        {
            server->sendMessage(ERR_USERONCHANNEL(client->getNickname(), nickname, channel_name), fd);
            return ; 
        }
        if (channel->isInviteOnly() && !channel->isClient(client->getNickname()))
        {
            server->sendMessage(ERR_NOTONCHANNEL(client->getNickname(), nickname), fd);
            return ;
        }
        if (channel->isInviteOnly() && !channel->isOperator(fd))
        {
            server->sendMessage(ERR_CHANOPRIVSNEEDED(client->getNickname(), channel_name), fd);
            return ;
        }
    }
    server->sendMessage(RPL_INVITING(client->getNickname(), nickname, channel_name), fd);



}