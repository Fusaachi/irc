#include "errors.hpp"
#include "../include/Commands.hpp"
#include "replies.hpp"


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
    std::string channel_name;
    std::string user_name;
    std::string reason;
    Client *client = server->getClient(fd);

    channel_name = get_channel_name(arg);
    user_name = get_user_name(arg);
    reason = get_reason(arg);
    if (channel_name.empty() || user_name.empty())
    {
        send_message(client, ERR_NEEDMOREPARAMS("KICK"));
        return ;

    }
    else if (!is_good_channel_mask(channel_name))
    {
        send_message(client, ERR_BADCHANMASK(channel_name, client->getNickname()));
        return ;
    }
    std::map<std::string, Channel*>::iterator it = server->getChannels().find(channel_name);
    if (it == server->getChannels().end())
    {
        send_message(client, ERR_NOSUCHCHANNEL(client->getNickname(), channel_name));
        return;
    }
    Channel *channel = it->second;
    if (!channel->isClient(fd))
    {
        send_message(client, ERR_NOTONCHANNEL(client->getNickname(), channel_name));
        return;
    }
    else if(!channel->isOperator(fd))
    {
        send_message(client, ERR_CHANOPRIVSNEEDED(client->getNickname(), channel_name));
        return ;
    }
    else if(!server->isClientIsInServer(user_name))
    {
        send_message(client, ERR_NOSUCHNICK(client->getNickname(), user_name));
        return;
    }
    else if(!channel->isClient(user_name))
    {
        send_message(client, ERR_USERNOTINCHANNEL(user_name, channel_name));
        return;
    }
    if (!reason.empty())
        reason = " : " + reason;
    channel->broadcast(RPL_KICK(client->getNickname(), client->getUsername(), channel_name, user_name, reason));
}