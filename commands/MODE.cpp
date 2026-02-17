#include "Server.hpp"
#include "Client.hpp"
#include "errors.hpp"
#include "replies.hpp"
#include "../include/Commands.hpp"

std::string get_flags(std::string const &arg)
{
    std::string flags;
    size_t pos = arg.find(' ');
    if (pos != std::string::npos && arg[pos + 1] )
    {
        flags = arg.substr(pos +1);
    }
    return (flags);
}

void Commands::MODE(Server *server, int fd, std::string arg)
{
    std::string name;
    std::string flags;
    Client *client = server->getClient(fd);

    if (name.empty() || flags.empty())
    {
        server->sendMessage(ERR_NEEDMOREPARAMS("MODE"), fd);
        return ;
    }
    if (name[0] == '#' || name[0] == '&')
    {

    }
    else
    {

    }
}