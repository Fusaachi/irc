#include "Server.hpp"
#include "Client.hpp"
#include "Commands.hpp"
#include "errors.hpp"

bool Commands::PASS(Server *server, int fd, std::string password)
{
    if (server->getClient(fd)->getHasPassword())
    {
        send_message(server->getClient(fd), ERR_ALREADYREGISTERED());
        return (false);
    }
    else if (password.size() == 0)
    {
        send_message(server->getClient(fd), ERR_NEEDMOREPARAMS("PASS"));
        return (false);
    }
    else if (password == server->getPassword())
    {
        server->getClient(fd)->setHasPassword(true);
        return(true);
    }
    else
    {
        send_message(server->getClient(fd), ERR_PASSWDMISMATCH(server->getClient(fd)->getNickname()));
        return(false);
    }
    return (true);
}