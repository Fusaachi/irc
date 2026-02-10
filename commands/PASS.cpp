#include "Server.hpp"
#include "Client.hpp"
#include "Commands.hpp"
#include "errors.hpp"

void Commands::PASS(Server *server, int fd, std::string password)
{
    Client *client = server->getClient(fd);
    if (client->getHasPassword())
    {
        send_message(client, ERR_ALREADYREGISTERED());
        return;
    }
    else if (password.size() == 0)
    {
        send_message(client, ERR_NEEDMOREPARAMS("PASS"));
        return;
    }
    else if (password == server->getPassword())
    {
        client->setHasPassword(true);
        return;
    }
    else
    {
        send_message(client, ERR_PASSWDMISMATCH(client->getNickname()));
        return;
    }
    return;
}