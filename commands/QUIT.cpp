#include "Server.hpp"
#include "Client.hpp"
#include "errors.hpp"
#include "replies.hpp"
#include "../include/Commands.hpp"

void Commands::QUIT(Server *server, int fd, std::string reason)
{
    if (reason.size() == 0)
        reason = "Leaving";
    server->sendMessage(MSG_QUIT(reason), fd);
    // ajouter client deconnecte au servuer

    return;
}