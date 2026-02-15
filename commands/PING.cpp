#include "../include/Commands.hpp"
#include "errors.hpp"
#include "replies.hpp"

void Commands::PING(Server *server, int fd, std::string arg)
{
    if (arg.empty())
        send_message(ERR_NOORIGIN(arg), fd);
    else 
        send_message(PONG(arg), fd);
}