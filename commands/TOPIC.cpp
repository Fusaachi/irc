#include "../include/Commands.hpp"
#include "errors.hpp"

void Commands::TOPIC(Server *server, int fd, std::string arg)
{
    std::string channel_name;
    std::string topic;
    if (channel_name.empty())
        send_message(ERR_NEEDMOREPARAMS("TOPIC"), fd);
    else if (!channel->isClient(fd))
        send_message(ERR_NOTONCHANNEL(client->getNickname(), channel_name), fd);
    else if (!)
    
    



}