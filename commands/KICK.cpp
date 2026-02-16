#include "errors.hpp"
#include "../include/Commands.hpp"
#include "replies.hpp"

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


std::vector<std::string> get_nicknames(std::string arg)
{
    int i = 0;
    std::string nickname;
    std::vector<std::string> nicknames;
    while (arg[i] && arg[i] != ' ')
        i++;
    if (!arg[i])
        return (nicknames);
    i++;
    while (arg[i])
    {
        while (arg[i] && arg[i] != ' ' && arg[i]!=',')
        {
            nickname += arg[i];
            i++;
        }
        nicknames.push_back(nickname);
        nickname = "";
        if (!arg[i] || isspace(arg[i]))
            break;        
        i++;
    }
    return (nicknames);
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
    while (arg[i])
    {
        name += arg[i];
        i++;
    }
    return (name);
}

bool is_good_channel_mask(std::string channel)
{
    if (channel.empty())
        return (false);
    if (!(channel[0] == '#' || channel[0] == '&'))
    {
        return (false);
    }
    for (int i = 1; channel[i]; i++)
    {
        if (channel[i] == ',' || channel[i] == ' '|| channel[i] == '\r'|| channel[i] == '\n')
            return (false);
    }
    return (true);
}

void Commands::KICK(Server *server, int fd, std::string arg)
{
    std::vector<std::string> channel_names;
    std::vector<std::string> nicknames;
    std::string reason;
    std::string channel_name;
    Client *client = server->getClient(fd);

    channel_names = get_channel_names(arg);
    nicknames = get_nicknames(arg);
    reason = get_reason(arg);
    if (channel_names.size() == 0 || nicknames.size() == 0 || (channel_names.size() > 1  && channel_names.size() != nicknames.size()))
    {
        send_message(ERR_NEEDMOREPARAMS("KICK"), fd);
        return ;
    }
    if (!reason.empty())
            reason = " : " + reason;
    for (size_t i = 0; i < nicknames.size(); i++)
    {
        if (channel_names.size() == 1)
            channel_name = channel_names[0];
        else
            channel_name = channel_names[i];
        // std::map<std::string, Channel*>::iterator it = server->getChannels().find(channel_name);
        // Channel *channel = it->second;
        Channel *channel = getChannel(channel_name);
        if (!is_good_channel_mask(channel_name))
            send_message(ERR_BADCHANMASK(channel_name, client->getNickname()), fd);
        // else if (it == server->getChannels().end())
        else if (!)
            send_message(ERR_NOSUCHCHANNEL(client->getNickname(), channel_name), fd);
        else if (!channel->isClient(fd))
            send_message(ERR_NOTONCHANNEL(client->getNickname(), channel_name), fd);
        else if(!channel->isOperator(fd))
            send_message(ERR_CHANOPRIVSNEEDED(client->getNickname(), channel_name), fd);
        // else if(!server->isClientIsInServer(nicknames[i]))
        //     send_message(client, ERR_NOSUCHNICK(client->getNickname(), nicknames[i]));
        else if(!channel->isClient(nicknames[i]))
            send_message(ERR_USERNOTINCHANNEL(nicknames[i], channel_name), fd);
        channel->broadcast(RPL_KICK(client->getNickname(), client->getUsername(), channel_name, nicknames[i], reason));
        server->getChannel(channel_name)->kick(nicknames[i]);
    }
}