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
        send_message(client, ERR_NONICKNAMEGIVEN());
        return;
    }
    else if(!is_good_nick(nick))
    {
        send_message(client, ERR_ERRONEUSNICKNAME(nick));
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
    if (client->getHasNickname())
    {
        std::string oldnickname = client->getNickname();
        client->setNickname(nick);
        send_message(client, MSG_NICK(oldnickname, client->getUsername(), "NICK", nick));
        return;
    }
    else
    {
        client->setNickname(nick);
        client->setHasNickname(true);
        if (client->getHasUsername() && client->getHasPassword())
        {
            client->setIsRegister(true);
            send_message(client, RPL_WELCOME(nick, client->getUsername));
            send_message(client, RPL_YOURHOST(nick));
            send_message(client, RPL_CREATED(nick));
        }
    }
    return;
}