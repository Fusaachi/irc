#include "../include/Commands.hpp"
#include "errors.hpp"
#include "replies.hpp"

void Commands::PING(Server *server, int fd, std::string arg)
{
    if (arg.empty())
        send_message(server->getClient(fd),ERR_NOORIGIN(arg));
    else 
        send_message(server->getClient(fd),PONG(arg));
}