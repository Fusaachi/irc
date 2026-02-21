#include "../include/Server.hpp"
#include "../include/Client.hpp"
#include "../include/Other.hpp"

bool is_topic(std::string const &arg)
{
    size_t pos = arg.find(' ');
    if (pos != std::string::npos && arg[pos + 1] && arg[pos + 1] == ':')
        return (true);
    return (false);

}

void Commands::TOPIC(Server *server, int fd, std::string arg)
{
    std::string channel_name;
    std::istringstream iss(arg);
    iss >> channel_name;
    if (channel_name.empty())
    {
        server->sendMessage(ERR_NEEDMOREPARAMS(client->getNickname() ,"TOPIC"), fd);
        return ;
    }
    Client *client = server->getClient(fd);
    Channel *channel = server->getChannel(channel_name);
    if (!channel)
    {
        server->sendMessage(ERR_NOSUCHCHANNEL(client->getNickname(), channel_name), fd);
        return;
    } 
    else if (!channel->isClient(fd))
    {
        server->sendMessage(ERR_NOTONCHANNEL(client->getNickname(), channel_name), fd);
        return ;

    }
    bool is_new_topic = is_topic(arg);
    std::string topic = get_reason(arg);
    std::string actual_topic = channel->getTopic();
    if (actual_topic.empty() && !is_new_topic)
    {
        server->sendMessage(RPL_NOTOPIC(client->getNickname(), channel_name), fd);
    }
    else if (!is_new_topic)
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