#include "Server.hpp"
#include "Client.hpp"
#include "errors.hpp"
#include "replies.hpp"

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

bool NICK(Server *server, Client *client, std::string nick)
{
    if (nick.size() == 0)
    {
        send_message(client, ERR_NONICKNAMEGIVEN());
        return (false);
    }
    else if(!is_good_nick(nick))
    {
        send_message(client, ERR_ERRONEUSNICKNAME(nick));
        return (false);
    }
    std::vector<Client> clients = server->getClients();
    for (int i = 0; i < clients.size(); i++)
    {
        if (clients[i].getNickname() == nick)
        {
            send_message(client, ERR_NICKNAMEINUSE(nick));
            return (false);
        }

    }
    if (client->hasNickName())
    {
        std::string oldnickname = client->getNickname();
        client->setNickname(nick);
        send_message(client, MSG_NICK(oldnickname, client->getUsername(), "NICK", nick));
        return (true);
    }
    else
    {
        client->setNickname(nick);
        client->setHasNickname(true);
        if (client->getHasUsername())
        {
            send_message(client, RPL_WELCOME(nick, client->getUsername));
            send_message(client, RPL_YOURHOST(nick));
            send_message(client, RPL_CREATED(nick));
        }
    }
    return (true);
}