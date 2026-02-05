#include "Server.hpp"
#include "Client.hpp"
#include "errors.hpp"

bool is_good_nick(std::string nick)
{
    if(!isalpha(nick[0]))
        return (false);
    for (int i = 1; i < nick.size(); i++)
    {
        if (!(isalnum(nick[i]) || '-' || '[' || ']' || '\' || '`' || '^' || '{' || '}'))

    }
    return (true);
    
}

bool NICK(Server *server, Client *client, std::string nick)
{
    if (nick.size() == 0)
    {
        send_error(client, ERR_NONICKNAMEGIVEN());
        return (false);
    }
    else if(!is_good_nick(nick))
    {
        send_error(client, ERR_ERRONEUSNICKNAME(nick));
        return (false);
    }
    else if 
    return (true);
}