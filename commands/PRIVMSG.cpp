#include "../include/Commands.hpp"
#include "errors.hpp"
#include "replies.hpp"
#include <set>


std::vector<std::string> get_name(std::string const &arg)
{
    int i = 0;
    std::string name;
    std::vector<std::string> names;
    while (arg[i])
    {
        while (arg[i] && arg[i]!=' ' && arg[i]!=',')
        {
            name +=arg[i];
            i++;

        }
        names.push_back(name);
        name = "";
        if (!arg[i] || arg[i] == ' ')
            break;        
        i++;
    }
    return (names);
}

std::string get_msg(std::string arg)
{
    int i = 0;
    int nbr_space = 0;
    std::string name;
    while (arg[i] && nbr_space != 1)
    {
        if (arg[i] == ' ')
            nbr_space++;
        i++;
    }
        i++;
    if (!arg[i] && arg[i] != ':')
        return (NULL);
    i++;
    while (arg[i])
    {
        name += arg[i];
        i++;
    }
    return (name);
}
// Channel *get_channel(Server *server, std::string name)
// {
//     std::map<std::string, Channel*>::iterator it = server->getChannels().find(name);
//     Channel *channel = it->second;
//     return (channel);
// }

void Commands::PRIVMSG(Server *server, int fd, std::string args)
{
    std::vector<std::string> receivers = get_name(args);
    std::string msg = get_msg(args);
    std::set<std::string> seen;
    Client *client = server->getClient(fd);
    if (receivers.size() == 0)
    {
        send_message(ERR_NORECIPIENT("PRIVMSG"), fd);
        return ;
    }
    else if (msg.empty())
    {
        send_message(ERR_NOTEXTTOSEND(client->getNickname()), fd);
        return ;
    }
    for (size_t i = 0; i < receivers.size(); i++)
    {
        if (!seen.insert(receivers[i]).second)
        {
            send_message(ERR_TOOMANYTARGETS(receivers[i]), fd);
        }
        else if (receivers[i][0] == '&' || receivers[i][0] == '#')
        {
            Channel *channel = server->getChannel(receivers[i]);
            if (!channel)
            {
                send_message(ERR_NOSUCHNICK(client->getNickname(), receivers[i]), fd);
            }
            else
            {
                channel->broadcast(RPL_PRIVMSG(client->getNickname(), client->getUsername(),receivers[i], msg));
            }
        }
        else
        {
            Client *client2 = server->getClient(receivers[i]);
            if (!client2)
            {
                send_message(ERR_NOSUCHNICK(client->getNickname(), receivers[i]), fd);
            }
            else 
            {
                send_message(RPL_PRIVMSG(client->getNickname(), client->getUsername(),receivers[i], msg), client2->getFd());
            }

        }
    }
}