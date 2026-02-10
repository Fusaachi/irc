#include "Server.hpp"
#include "Client.hpp"
#include "errors.hpp"
#include "replies.hpp"

bool QUIT(Server *server, Client *client, std::string reason)
{
    if (reason.size() == 0)
        reason = "Leaving";
    send_message(client, MSG_QUIT(reason));
    // ajouter client deconnecte au servuer

    return (true);
}