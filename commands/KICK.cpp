#include "errors.hpp"
#include "../include/Commands.hpp"
#include "replies.hpp"

std::vector<std::string> get_names_channels(std::string const &arg)
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


std::vector<std::string> get_users_names(std::string arg)
{
    int i = 0;
    std::string user_name;
    std::vector<std::string> users_names;
    while (arg[i] && arg[i] != ' ')
        i++;
    if (!arg[i])
        return (users_names);
    i++;
    while (arg[i])
    {
        while (arg[i] && arg[i] != ' ' && arg[i]!=',')
        {
            user_name += arg[i];
            i++;
        }
        users_names.push_back(user_name);
        user_name = "";
        if (!arg[i] || isspace(arg[i]))
            break;        
        i++;

    }

    return (users_names);
}

std::string get_reason(std::string arg)
{
    int i = 0;
    int nbr_space = 0;
    std::string name;
    while (arg[i] && nbr_space != 2)
    {
        if (arg[i] == ' ')
            nbr_space++;
        i++;
    }
        i++;
    if (!arg[i] && arg[i] != ':')
        return (NULL);
    i++;
    while (arg[i] && arg[i] != ' ')
    {
        name += arg[i];
        i++;
    }
    return (name);
}

bool is_good_channel_mask(std::string channel)
{
    if (!(channel[0] == '#' || channel[0] == '&'))
    {
        return (false);
    }
    for (int i = 1; channel[i]; i++)
    {
        if (channel[i] == ',')
            return (false);
    }
    return (true);
}

void Commands::KICK(Server *server, int fd, std::string arg)
{
    std::vector<std::string> names_channels;
    std::vector<std::string> users_names;
    std::string reason;
    std::string channel_name;
    Client *client = server->getClient(fd);

    names_channels = get_names_channels(arg);
    users_names = get_users_names(arg);
    reason = get_reason(arg);
    if (names_channels.size() == 0 || users_names.size() == 0 || (names_channels.size() > 1  && names_channels.size() != users_names.size()))
    {
        send_message(client, ERR_NEEDMOREPARAMS("KICK"));
        return ;
    }
    for (size_t i = 0; i < users_names.size(); i++)
    {
        if (names_channels.size() == 1)
            channel_name = names_channels[1];
        else
            channel_name = names_channels[i];
        std::map<std::string, Channel*>::iterator it = server->getChannels().find(channel_name);
        Channel *channel = it->second;
        if (!is_good_channel_mask(channel_name))
            send_message(client, ERR_BADCHANMASK(channel_name, client->getNickname()));
        else if (it == server->getChannels().end())
            send_message(client, ERR_NOSUCHCHANNEL(client->getNickname(), channel_name));
        else if (!channel->isClient(fd))
            send_message(client, ERR_NOTONCHANNEL(client->getNickname(), channel_name));
        else if(!channel->isOperator(fd))
            send_message(client, ERR_CHANOPRIVSNEEDED(client->getNickname(), channel_name));
        else if(!server->isClientIsInServer(users_names[i]))
            send_message(client, ERR_NOSUCHNICK(client->getNickname(), users_names[i]));
        else if(!channel->isClient(users_names[i]))
            send_message(client, ERR_USERNOTINCHANNEL(user_name, channel_name));
        else if (!reason.empty())
            reason = " : " + reason;
        channel->broadcast(RPL_KICK(client->getNickname(), client->getUsername(), channel_name, users_names[i], reason));
        server->getChannel(channel_name)->kick(users_names[i]);
    }
}