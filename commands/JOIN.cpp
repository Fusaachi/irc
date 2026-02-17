#include "Server.hpp"
#include "Client.hpp"
#include "errors.hpp"
#include "replies.hpp"
#include "../include/Commands.hpp"

std::vector<std::string> get_channel_names(std::string const &arg)
{
    int i = 0;
    std::string channel_name;
    std::vector<std::string> channel_names;
    while (arg[i])
    {
        while (arg[i] && !isspace(arg[i]) && arg[i]!=',')
        {
            channel_name +=arg[i];
            i++;

        }
        channel_names.push_back(channel_name);
        channel_name = "";
        if (!arg[i] || isspace(arg[i]))
            break;        
        i++;
    }
    return (channel_names);
}
std::vector<std::string> get_keys(std::string arg)
{
    int i = 0;
    std::string key;
    std::vector<std::string> keys;
    while (arg[i] && arg[i] != ' ')
        i++;
    if (!arg[i])
        return (keys);
    i++;
    while (arg[i])
    {
        while (arg[i] && arg[i] != ' ' && arg[i]!=',')
        {
            key += arg[i];
            i++;
        }
        keys.push_back(key);
        key = "";
        if (!arg[i] || isspace(arg[i]))
            break;        
        i++;
    }
    return (keys);
}
void Commands::JOIN(Server *server, int fd, std::string arg)
{
    std::vector<std::string> channel_names = get_channel_names(arg);
    std::vector<std::string> keys = get_keys(arg);
    Client *client = server->getClient(fd);

    if (channel_names.size() == 0)
    {
        server->sendMessage(ERR_NEEDMOREPARAMS("JOIN"), fd);
        return ;
    }
    for (int i = 0; i < channel_names.size(); i++)
    {
        if (channel_names[i].empty() || !(channel_names[i][0] == '&' || channel_names[i][0] == '#'))
        {
            server->sendMessage(ERR_BADCHANMASK(channel_names[i], client->getNickname()), fd);
            continue;
        }
        if (client->getNbrChannel() > MAX_NBR_CHANNEL)
        {
            server->sendMessage(ERR_TOOMANYCHANNELS(client->getNickname(), channel_names[i]), fd);
            continue;

        }
        Channel *channel = server->getChannel(channel_names[i]);
        if (!channel)
        {
            channel = server->addChannel(channel_names[i], client);
            continue;
        }
        if (channel->hasModeI() && !channel->isInvited(fd))
        {
            server->sendMessage(ERR_INVITEONLYCHAN(client->getNickname(), channel_names[i]), fd);
            return ;
        }

    
        
    }

    
}