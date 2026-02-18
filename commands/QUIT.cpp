#include "../include/Server.hpp"
#include "../include/Client.hpp"
#include "../include/Other.hpp"

void Commands::QUIT(Server *server, int fd, std::string reason)
{
    if (reason.size() == 0)
        reason = "Leaving";
    server->sendMessage(MSG_QUIT(reason), fd);
    // ajouter client deconnecte au servuer

    return;
}