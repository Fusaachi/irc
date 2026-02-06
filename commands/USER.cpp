#include "Server.hpp"
#include "Client.hpp"
#include "errors.hpp"
#include "replies.hpp"

bool USER(Server *server, Client *client, std::string user)
{
    if (client->getHasPassword() == false)
    {
        return (false);
    }
    if (user.size() == 0)
    {
        send_message(client,ERR_NEEDMOREPARAMS("USER"));
        return (false);
    }
    else if (client->getHasUsername())
    {
        send_message(client, ERR_ALREADYREGISTERED());
        return (false);
    }
    else 
    {
        client->setUsername = user;
        client->setHasUsername() = true;
        if (client->getHasUsername())
        {
            client->setIsRegister = true;
            send_message(client, RPL_WELCOME(client->getNickname(), user));
            send_message(client, RPL_YOURHOST(client->getNickname()));
            send_message(client, RPL_CREATED(client->getNickname()));
        }
        return (true);

    }
}