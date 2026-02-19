#include "../include/Server.hpp"
#include "../include/Client.hpp"
#include "../include/Other.hpp"

void Commands::USER(Server *server, int fd, std::string user)
{
    Client *client = server->getClient(fd);
    if (user.size() == 0)
    {
        server->sendMessage(ERR_NEEDMOREPARAMS("USER"), fd);
        return;
    }
    else if (client->getHasUsername())
    {
        server->sendMessage(ERR_ALREADYREGISTERED(), fd);
        return;
    }
    else 
    {
        client->setUsername(user);
        client->setHasUsername(true);
        if (client->getHasPassword() && client->getHasNickname())
        {
            client->setIsRegister(true);
            server->sendMessage(RPL_WELCOME(client->getNickname(), user), fd);
            server->sendMessage(RPL_YOURHOST(client->getNickname()), fd);
            server->sendMessage(RPL_CREATED(client->getNickname()), fd);
        }
        return;
    }
}