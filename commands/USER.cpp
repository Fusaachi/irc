#include "../include/Server.hpp"
#include "../include/Client.hpp"
#include "../include/Commands.hpp"
#include "errors.hpp"
#include "replies.hpp"

void Commands::USER(Server *server, int fd, std::string user)
{
    if (client->getHasPassword() == false)
    {
        return;
    }
    if (user.size() == 0)
    {
        send_message(client,ERR_NEEDMOREPARAMS("USER"));
        return;
    }
    else if (client->getHasUsername())
    {
        send_message(client, ERR_ALREADYREGISTERED());
        return;
    }
    else 
    {
        client->setUsername(user);
        client->setHasUsername(true);
        if (client->getHasUsername())
        {
            client->setIsRegister(true);
            send_message(client, RPL_WELCOME(client->getNickname(), user));
            send_message(client, RPL_YOURHOST(client->getNickname()));
            send_message(client, RPL_CREATED(client->getNickname()));
        }
        return;

    }
}