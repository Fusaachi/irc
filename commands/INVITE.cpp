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
    }


}