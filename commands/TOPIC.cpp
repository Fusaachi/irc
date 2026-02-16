#include "../include/Commands.hpp"
#include "errors.hpp"
#include "replies.hpp"

std::string get_channel_name(std::string arg)
{
    int i = 0
    std::string name;
    while(arg[i] && !isspace(arg[i]))
    {
        name +=arg[i];
        i++;
    }
    return (name);
}
std::string get_topic(std::string arg)
{
    std::string topic;
    size_t space = arg.find(' ');
    if (space == std::string::npos)
        return (NULL);
    else
    {
        topic = args.substr(space + 1);
        if (!topic.empty() && topic[0] == ':')
        topic = topic.substr(1);
        return (topic);
    }
}


void Commands::TOPIC(Server *server, int fd, std::string arg)
{
    std::string channel_name = get_channel_name(arg);
    std::string topic = get_topic(arg);
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