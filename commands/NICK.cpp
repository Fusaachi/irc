#include "../include/Server.hpp"
#include "errors.hpp"
#include "replies.hpp"
#include "../include/Commands.hpp"

bool is_good_nick(std::string nick)
{
    if(!isalpha(nick[0]))
        return (false);
    for (size_t i = 1; i < nick.size(); i++)
    {
        if (!(isalnum(nick[i]) || nick[i]== '-' || nick[i]== '[' || nick[i]== ']' || nick[i]== '\\' || nick[i]== '`' || nick[i]== '^' || nick[i]== '{' || nick[i]== '}'))
            return (false);
    }
    return (true);
    
}

void Commands::NICK(Server *server, int fd, std::string nick)
{
    Client *client = server->getClient(fd);
    if (nick.size() == 0)
    {
        server->sendMessage(ERR_NONICKNAMEGIVEN(), fd);
        return;
    }
    else if(!is_good_nick(nick))
    {
        server->sendMessage(ERR_ERRONEUSNICKNAME(nick), fd);
        return;
    }
    for (std::map<int, Client *>::iterator it = server->getClients().begin(); it != server->getClients().end(); it++)
    {
        if (it->second->getNickname() == nick)
        {
            server->sendMessage(ERR_NICKNAMEINUSE(nick), fd);
            return;
        }
    }
    if (client->getHasNickname())
    {
        std::string oldnickname = client->getNickname();
        client->setNickname(nick);
        server->sendMessage(MSG_NICK(oldnickname, client->getUsername(), "NICK", nick), fd);
        return;
    }
    else
    {
        client->setNickname(nick);
        client->setHasNickname(true);
        if (client->getHasUsername() && client->getHasPassword())
        {
            client->setIsRegister(true);
            server->sendMessage(RPL_WELCOME(nick, client->getUsername), fd);
            server->sendMessage(RPL_YOURHOST(nick), fd);
            server->sendMessage(RPL_CREATED(nick), fd);
        }
    }
    return;
}