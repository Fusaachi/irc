#include "../include/Server.hpp"
#include "../include/Client.hpp"
#include "../include/Other.hpp"


void Commands::PASS(Server *server, int fd, std::string password)
{
    Client *client = server->getClient(fd);
    if (client->getHasPassword())
    {
        server->sendMessage(ERR_ALREADYREGISTERED(), fd);
        return;
    }
    else if (password.size() == 0)
    {
        server->sendMessage(ERR_NEEDMOREPARAMS("PASS"), fd);
        return;
    }
    else if (password == server->getPassword())
    {
        client->setHasPassword(true);
        return;
    }
    else
    {
        server->sendMessage(ERR_PASSWDMISMATCH(client->getNickname()), fd);
        return;
    }
    return;
}