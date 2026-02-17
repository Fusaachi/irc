#include "../include/Commands.hpp"
#include "errors.hpp"
#include "replies.hpp"

void Commands::PING(Server *server, int fd, std::string arg)
{
    if (arg.empty())
        server->sendMessage(ERR_NOORIGIN(arg), fd);
    else 
        server->sendMessage(PONG(arg), fd);
}