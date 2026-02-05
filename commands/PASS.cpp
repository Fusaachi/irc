#include "Server.hpp"
#include "Client.hpp"
#include "errors.hpp"

bool PASS(Server *server, Client *client, std::string password)
{
    if (client.hasPassword())
    {
        send_error(client, ERR_ALREADYREGISTERED());
        return (false);
    }
    else if (password.size() == 0)
    {
        send_error(client, ERR_NEEDMOREPARAMS("PASS"));
        return (false);
    }
    return (true);
}