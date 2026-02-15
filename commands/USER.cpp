#include "../include/Server.hpp"
#include "../include/Client.hpp"
#include "../include/Commands.hpp"
#include "errors.hpp"
#include "replies.hpp"

void Commands::USER(Server *server, int fd, std::string user)
{
    Client *client = server->getClient(fd);
    if (client->getHasPassword() == false)
    {
        return;
    }
    if (user.size() == 0)
    {
        send_message(ERR_NEEDMOREPARAMS("USER"), fd);
        return;
    }
    else if (client->getHasUsername())
    {
        send_message(ERR_ALREADYREGISTERED(), fd);
        return;
    }
    else 
    {
        client->setUsername(user);
        client->setHasUsername(true);
        if (client->getHasUsername())
        {
            client->setIsRegister(true);
            send_message(RPL_WELCOME(client->getNickname(), user), fd);
            send_message(RPL_YOURHOST(client->getNickname()), fd);
            send_message(RPL_CREATED(client->getNickname()), fd);
        }
        return;

    }
}