#include "Server.hpp"
#include "Client.hpp"
#include "errors.hpp"
#include "replies.hpp"
#include "../include/Commands.hpp"
#include <sstream>

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
    std::string third_arg;
    bool is_add = false;
    bool is_del = false;
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
        if (flags.empty())
        {
            server->sendMessage(RPL_MODE(client->getNickname(),client->getUsername(), name, channel->getModes()), fd);
            return ;
        }
        for (int i = 0; i < flags.size(); i++)
            {
                if (flags[i] == '+')
                {
                    is_add = true;
                    is_del = false;
                }
                else if (flags[i] == '-')
                {
                    is_add = false;
                    is_del = true;
                }
                else if (flags[i] == 'i')
                {
                    if (is_add)
                        channel->setInviteOnly(true);
                    else if (is_del)
                        channel->setInviteOnly(false);
                }
                else if (flags[i] == 't')
                {
                    if (is_add)
                        channel->setTopicRestricted(true);
                    else if (is_del)
                        channel->setTopicRestricted(false);
                }
                else if (flags[i] == 'k')
                {
                    if (is_add && !third_arg.empty())
                    {
                        channel->setPwd(third_arg);
                        channel->setModeK(true);
                    }
                    else if (is_add && third_arg.empty())
                    {
                        server->sendMessage(ERR_NEEDMOREPARAMS("MODE"), fd);
                        continue ;
                    }
                    else if (is_del)
                    {
                        channel->setModeK(false);
                    }
                }
                else if (flags[i] == 'o')
                {
                    if ((is_add || is_del) && third_arg.empty())
                    {
                        server->sendMessage(ERR_NEEDMOREPARAMS("MODE"), fd);
                        continue;
                    }
                    else if (third_arg.empty())
                    {
                        server->sendMessage(RPL_MODE(client->getNickname(),client->getUsername(), name, channel->getModes()), fd);
                        continue;
                    }
                    if (!channel->isClient(third_arg))
                    {
                        server->sendMessage(ERR_NOTONCHANNEL(client->getNickname(), third_arg), fd);
                        continue;
                    }
                    if (is_add)
                    {
                        channel->addOperator(third_arg);
                    }

                    else if (is_del)
                    {
                        channel->delOperator(third_arg);
                    }

                }
                else if (flags[i] == 'l')
                {
                    if (is_del)
                    {
                        channel->setHasUserLimit(false);
                        continue;
                    }
                    if (is_add && third_arg.empty())
                    {
                        server->sendMessage(ERR_NEEDMOREPARAMS("MODE"), fd);
                        continue;
                    }
                    int number;
                    std::istringstream iss(third_arg);
                    if (iss >> number && number > 0)
                    {
                        channel->setHasUserLimit(true);
                        channel->setMaxUser(number);
                        continue;
                    }
                    else
                    {
                        server->sendMessage(ERR_NEEDMOREPARAMS("MODE"), fd);
                        continue;
                    }
                }
                else
                {
                    server->sendMessage(ERR_UNKNOWNMODE(client->getNickname(), flags[i]), fd);
                    continue;
                }

            }

        }
            server->sendMessage(RPL_MODE(client->getNickname(),client->getUsername(), name, channel->getModes()), fd);
            return;

}