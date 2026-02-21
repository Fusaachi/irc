#include "../include/Server.hpp"
#include "../include/Client.hpp"
#include "../include/Other.hpp"

void Commands::QUIT(Server *server, int fd, std::string reason)
{
    Client *client = server->getClient(fd);
    if (reason.size() == 0)
        reason = "Leaving";
    server->sendMessage(MSG_QUIT(client->getNickname() ,reason), fd);
    // ajouter client deconnecte au servuer

    return;
}