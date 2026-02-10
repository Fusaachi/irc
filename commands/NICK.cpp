#include "Server.hpp"
#include "Client.hpp"
#include "errors.hpp"
#include "replies.hpp"
#include "../include/Commands.hpp"

bool is_good_nick(std::string nick)
{
    if(!isalpha(nick[0]))
        return (false);
    for (int i = 1; i < nick.size(); i++)
    {
        if (!(isalnum(nick[i]) || nick[i]== '-' || nick[i]== '[' || nick[i]== ']' || nick[i]== '\\' || nick[i]== '`' || nick[i]== '^' || nick[i]== '{' || nick[i]== '}'))
            return (false);
    }
    return (true);
    
}

void Commands::NICK(Server *server, int fd, std::string nick)
{
    if (nick.size() == 0)
    {
        send_message(server->getClient(fd), ERR_NONICKNAMEGIVEN());
        return;
    }
    else if(!is_good_nick(nick))
    {
        send_message(server->getClient(fd), ERR_ERRONEUSNICKNAME(nick));
        return;
    }
    for (std::map<int, Client *>::iterator it = server->getClients().begin(); it != server->getClients().end(); it++)
    {
        if (it->second->getNickname() == nick)
        {
            send_message(server->getClient(it->first), ERR_NICKNAMEINUSE(nick));
            return;
        }
    }
    if (server->getClient(fd)->getHasNickname())
    {
        std::string oldnickname = server->getClient(fd)->getNickname();
        server->getClient(fd)->setNickname(nick);
        send_message(server->getClient(fd), MSG_NICK(oldnickname, server->getClient(fd)->getUsername(), "NICK", nick));
        return;
    }
    else
    {
        server->getClient(fd)->setNickname(nick);
        server->getClient(fd)->setHasNickname(true);
        if (server->getClient(fd)->getHasUsername() && server->getClient(fd)->getHasPassword())
        {
            server->getClient(fd)->setIsRegister(true);
            send_message(server->getClient(fd), RPL_WELCOME(nick, server->getClient(fd)->getUsername));
            send_message(server->getClient(fd), RPL_YOURHOST(nick));
            send_message(server->getClient(fd), RPL_CREATED(nick));
        }
    }
    return;
}