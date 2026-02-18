#include "Server.hpp"
#include "Client.hpp"
#include "errors.hpp"
#include "replies.hpp"
#include "../include/Commands.hpp"

std::string get_flags(std::string const &arg)
{
    std::string flags;
    size_t pos = arg.find(' ');
    if (pos != std::string::npos && arg[pos + 1] )
    {
        flags = arg.substr(pos +1);
    }
    return (flags);
}

void Commands::MODE(Server *server, int fd, std::string arg)
{
    std::string name;
    std::string flags;
    Client *client = server->getClient(fd);

    if (name.empty() || flags.empty())
    {
        server->sendMessage(ERR_NEEDMOREPARAMS("MODE"), fd);
        return ;
    }
    if (name[0] == '#' || name[0] == '&')
    {
        Channel *channel = server->getChannel(name);
        if (!channel)
        {
            server->sendMessage(ERR_NOSUCHCHANNEL(client->getNickname(), name), fd);
            return;
        }
        if (!channel->isClient(fd))
        {
            server->sendMessage(ERR_NOTONCHANNEL(client->getNickname(), name), fd);
            return;
        }
        if (!channel->isOperator(fd))
        {
            server->sendMessage(ERR_CHANOPRIVSNEEDED(client->getNickname(), name), fd);
            return;
        }
        
        if (flags[0] == '-')
        {
            for (int i = i; i < flags.size(); i++)
            {
                if (flags[i] == 'i')
                {

                }
                else if (flags[i] == 't')
                {

                }
                else if (flags[i] == 'k')
                {

                }
                else if (flags[i] == 'o')
                {

                }
                else if (flags[i] == 'l')
                {

                }
                else
                {
                    server->sendMessage(ERR_UNKNOWNMODE(client->getNickname(), flags[i]), fd);
                    return;
                }

            }

        }
        if (flags[0] == '+')
        {
            for (int i = i; i < flags.size(); i++)
            {
                
            }
        }
        else 
        {
            server->sendMessage(RPL_MODE(client->getNickname(),client->getUsername(), name, channel->getModes()), fd);
            return;
        }

    }
    else
    {

    }
}