#include "../include/Commands.hpp"
#include "errors.hpp"
#include "replies.hpp"

void Commands::TOPIC(Server *server, int fd, std::string arg)
{
    std::string channel_name;
    std::string topic;
    if (channel_name.empty())
    {
        send_message(ERR_NEEDMOREPARAMS("TOPIC"), fd);
        return ;
    }
    Channel *channel = getChannel(channel_name)
    if (!channel)
        send_message(ERR_NOSUCHCHANNEL(client->getNickname(), channel_name), fd);
    else if (!channel->isClient(fd))
    {
        send_message(ERR_NOTONCHANNEL(client->getNickname(), channel_name), fd);
        return ;

    }
    std::string actual_topic = channel.getTopic();
    if (!actual_topic && topic.empty())
    {
        send_message(RPL_NOTOPIC(client->getNickname(), channel_name), fd);
    }
    else if (topic.empty())
    {
        send_message(RPL_TOPIC(client->getNickname(), channel_name, actual_topic), fd);
    }
    else if (channel.isModeT() && !channel.isOperator(fd))
    {
        send_message(ERR_CHANOPRIVSNEEDED(client->getNickname(), channel_name), fd);
    }
    else 
    {
        channel->setTopic(topic);
        channel->broadcast(MSG_TOPIC(client->getNickname(), client->getUsername(), channel_name, topic));
    }
}