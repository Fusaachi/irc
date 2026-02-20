#include "../include/Server.hpp"
#include "../include/Client.hpp"
#include "../include/Other.hpp"

std::vector<std::string> get_nick(std::string arg)
{
    int i = 0;
    std::string nickname;
    std::vector<std::string> nicknames;
    while (arg[i])
    {
        while (arg[i] && arg[i]!=',')
        {
            nickname += arg[i];
            i++;
        }
        nicknames.push_back(nickname);
        nickname = "";
        if (!arg[i])
            break;        
        i++;
    }
    return (nicknames);
}

void Commands::PRIVMSG(Server *server, int fd, std::string args)
{
    std::vector<std::string> receivers;
    std::istringstream iss(args);
    std::string msg;
    std::string str_receivers;
    std::set<std::string> seen;
    iss >> str_receivers >> msg;
    Client *client = server->getClient(fd);
    if (str_receivers.size() == 0)
    {
        server->sendMessage(ERR_NORECIPIENT(client->getNickname(), "PRIVMSG"), fd);
        return ;
    }
    else if (msg.empty())
    {
        server->sendMessage(ERR_NOTEXTTOSEND(client->getNickname()), fd);
        return ;
    }
    receivers = get_nick(str_receivers);
    for (size_t i = 0; i < receivers.size(); i++)
    {
        if (!seen.insert(receivers[i]).second)
        {
            server->sendMessage(ERR_TOOMANYTARGETS(client->getNickname(), receivers[i]), fd);
        }
        else if (receivers[i][0] == '&' || receivers[i][0] == '#')
        {
            Channel *channel = server->getChannel(receivers[i]);
            if (!channel)
            {
                server->sendMessage(ERR_NOSUCHNICK(client->getNickname(), receivers[i]), fd);
            }
            else
            {
                channel->broadcast(RPL_PRIVMSG(client->getNickname(), client->getUsername(),receivers[i], msg), fd);
            }
        }
        else
        {
            Client *client2 = server->getClient(receivers[i]);
            if (!client2)
            {
                server->sendMessage(ERR_NOSUCHNICK(client->getNickname(), receivers[i]), fd);
            }
            else 
            {
                server->sendMessage(RPL_PRIVMSG(client->getNickname(), client->getUsername(),receivers[i], msg), client2->getFd());
            }

        }
    }
}