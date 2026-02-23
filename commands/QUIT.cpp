#include "../include/Server.hpp"
#include "../include/Client.hpp"
#include "../include/Other.hpp"

void Commands::QUIT(Server *server, int fd, std::string reason)
{
    Client *client = server->getClient(fd);
    std::map<std::string, Channel*> channels = server->getChannels();
    if (reason.size() == 0)
        reason = "Leaving";   
    for (std::map<std::string, Channel*>::iterator it = channels.begin(); it != channels.end(); it++)
    {
        Channel *channel = it->second;
        if (channel->isClient(fd))
        {
            channel->broadcast(MSG_QUIT(client->getNickname() ,reason), -1);
            channel->delUser(client->getNickname());
        }
    }
	
    server->clientDisconnect(fd);
}