#include "../include/Server.hpp"
#include "../include/Client.hpp"
#include "../include/Other.hpp"

void Commands::MODE(Server *server, int fd, std::string arg)
{
    std::string name;
    std::string flags;
    std::istringstream iss(arg);
    std::vector<std::string> params;
    std::string param;
    bool is_add = false;
    bool is_del = false;
    Client *client = server->getClient(fd);
    size_t j = 0;

    iss >> name >> flags;
    while (iss >> param)
        params.push_back(param);

    if (name.empty() || flags.empty())
    {
        server->sendMessage(ERR_NEEDMOREPARAMS(client->getNickname(), "MODE"), fd);
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
        for (size_t i = 0; i < flags.size(); i++)
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
                        channel->setModeI(true);
                    else if (is_del)
                        channel->setModeI(false);
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
                    if (is_add && j < params.size())
                    {
                        channel->setPwd(params[j]);
                        channel->setModeK(true);
                        j++;
                    }
                    else if (is_add && j == params.size())
                    {
                        server->sendMessage(ERR_NEEDMOREPARAMS(client->getNickname(), "MODE"), fd);
                        continue ;
                    }
                    else if (is_del)
                    {
                        channel->setModeK(false);
                    }
                }
                else if (flags[i] == 'o')
                {
                    if ((is_add || is_del) && j == params.size())
                    {
                        server->sendMessage(ERR_NEEDMOREPARAMS(client->getNickname(), "MODE"), fd);
                        continue;
                    }
                    if (!channel->isClient(params[j]))
                    {
                        server->sendMessage(ERR_NOTONCHANNEL(client->getNickname(), params[j]), fd);
                        continue;
                    }
                    Client *client2 = server->getClient(params[j]);
                    if (is_add)
                    {
                        channel->addOperator(client2->getFd());
                    }

                    else if (is_del)
                    {
                        channel->delOperator(client2->getFd());
                    }

                }
                else if (flags[i] == 'l')
                {
                    if (is_del)
                    {
                        channel->setHasUserLimit(false);
                        continue;
                    }
                    if (is_add && j == params.size())
                    {
                        server->sendMessage(ERR_NEEDMOREPARAMS(client->getNickname(), "MODE"), fd);
                        continue;
                    }
                    int number;
                    std::istringstream iss(params[j]);
                    if (iss >> number && number > 0)
                    {
                        channel->setHasUserLimit(true);
                        channel->setMaxUser(number);
                        continue;
                    }
                    else
                    {
                        server->sendMessage(ERR_NEEDMOREPARAMS(client->getNickname(), "MODE"), fd);
                        continue;
                    }
                }
                else
                {
                    server->sendMessage(ERR_UNKNOWNMODE(client->getNickname(), flags[i]), fd);
                    continue;
                }

            }
            server->sendMessage(RPL_MODE(client->getNickname(),client->getUsername(), name, channel->getModes()), fd);
            return;
        }
        else 
        {
            server->sendMessage(ERR_BADCHANMASK(client->getNickname(), name), fd);
            return;
        }


}





// int main(void)
// {
//     std::string oui = "#channel +kl secretpassword 50 ouiiiiiiiiii";
//     std::string name;
//     std::string flags;
//     std::vector<std::string> params;
//     std::string param;
//     std::istringstream iss(oui);
//     iss >> name >> flags;
//     while (iss >> param)
//         params.push_back(param);
//     std::cout << "Z" << name << "Z" << flags << "Z" << std::endl;
//     std::cout << "U" << params[0] << "U" << params[1] << "U" <<  params[2] << "U" << std::endl;
//     return (0);
// }