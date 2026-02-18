#include "../include/Server.hpp"
#include "../include/Client.hpp"
#include "../include/Other.hpp"

std::string get_channel_name(std::string arg)
{
    int i = 0;
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
        topic = arg.substr(space + 1);
        if (!topic.empty() && topic[0] == ':')
        topic = topic.substr(1);
        return (topic);
    }
}


void Commands::TOPIC(Server *server, int fd, std::string arg)
{
    std::string channel_name = get_channel_name(arg);
    std::string topic = get_topic(arg);
    Client *client = server->getClient(fd);
    if (channel_name.empty())
    {
        server->sendMessage(ERR_NEEDMOREPARAMS("TOPIC"), fd);
        return ;
    }
    Channel *channel = server->getChannel(channel_name);
    if (!channel)
        server->sendMessage(ERR_NOSUCHCHANNEL(client->getNickname(), channel_name), fd);
    else if (!channel->isClient(fd))
    {
        server->sendMessage(ERR_NOTONCHANNEL(client->getNickname(), channel_name), fd);
        return ;

    }
    std::string actual_topic = channel->getTopic();
    if (actual_topic.empty() && topic.empty())
    {
        server->sendMessage(RPL_NOTOPIC(client->getNickname(), channel_name), fd);
    }
    else if (topic.empty())
    {
        server->sendMessage(RPL_TOPIC(client->getNickname(), channel_name, actual_topic), fd);
    }
    else if (channel->hasModeT() && !channel->isOperator(fd))
    {
        server->sendMessage(ERR_CHANOPRIVSNEEDED(client->getNickname(), channel_name), fd);
    }
    else 
    {
        channel->setTopic(topic);
        channel->broadcast(MSG_TOPIC(client->getNickname(), client->getUsername(), channel_name, topic), fd);
    }
}