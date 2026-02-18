#include "../include/Server.hpp"
#include "../include/Client.hpp"
#include "../include/Other.hpp"


std::vector<std::string> get_names_channels(std::string const &arg)
{
    int i = 0;
    int k;
    std::string channel_name;
    std::vector<std::string> channel_names;
    while (arg[i])
    {
        if (!(arg[i] == '#' || arg[i] == '&'))
        {
            break;
        }
        k = i;
        while (arg[k] && !isspace(arg[k]) && arg[k]!=',')
        {
            channel_name +=arg[k];
            k++;

        }
        channel_names.push_back(channel_name);
        channel_name = "";
        if (isspace(arg[k]) || !arg[k])
            break;        
        i = k + 1;
    }
    return (channel_names);
}

std::string get_reason(std::string const &arg)
{
    std::string reason;
    size_t pos = arg.find(' ');
    if (pos != std::string::npos && arg[pos + 1] && arg[pos + 1] == ':' && arg[pos + 2])
    {
        reason = arg.substr(pos +2);
    }
    return (reason);

}



void Commands::PART(Server *server, int fd, std::string arg)
{
    Client *client = server->getClient(fd);   
    if (arg.size() == 0)
    {
        server->sendMessage(ERR_NEEDMOREPARAMS("PART"), fd);
        return;
    }
    std::vector<std::string> channel_names = get_names_channels(arg);
    if (channel_names[0].empty())
    {
        server->sendMessage(ERR_BADCHANMASK(arg, client->getNickname()), fd);
    }
    std::string reason = get_reason(arg);
    for (std::string name : channel_names)
    {
        // std::map<std::string, Channel*>::iterator it = server->getChannels().find(name);
        Channel *channel = server->getChannel(name);
	    // if (it == server->getChannels().end())
        if (!channel)
        {
           server->sendMessage(ERR_NOSUCHCHANNEL(client->getNickname(), name), fd);
           return;
        }
        // Channel *channel = it->second;
		if (!channel->isClient(client->getFd()))
		{
			server->sendMessage(ERR_NOTONCHANNEL(client->getNickname(), name), fd);
			return;
		}
        else 
        {
            channel->part(fd);
            if (!reason.empty())
            {
                reason = " : " + reason;
            }
            channel->delUser(client->getNickname());
            channel->broadcast(RPL_PART(client->getNickname(), client->getUsername(), "PART", channel->getChannelName(), reason));
            if (channel->isEmpty())
            {
                delete(channel);
                server->removeChannel(name);
            }

        }
    }
}


// int main(int argc, char **argv)
// {
//     (void)argc;
//     std::vector<std::string> channel_names;
//     std::string reason;
//     std::string arg;
//     channel_names = get_names_channels(argv[1]);
//     for (std::string n : channel_names)
//     {
//         std::cout << n << "      " << std::endl;
//     }
//     reason = get_reason(argv[1]);
//     if (!reason.empty())
//     {
//         std::cout << "REASON : " << reason << std::endl;
//     }
//     return (0);
// }