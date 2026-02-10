#include "Server.hpp"
#include "Client.hpp"
#include "errors.hpp"
#include "replies.hpp"
#include "../include/Commands.hpp"

bool Commands::QUIT(Server *server, int fd, std::string reason)
{
    if (reason.size() == 0)
        reason = "Leaving";
    send_message(server->getClient(fd), MSG_QUIT(reason));
    // ajouter client deconnecte au servuer

    return (true);
}