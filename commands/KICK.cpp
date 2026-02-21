#include "../include/Server.hpp"
#include "../include/Client.hpp"
#include "../include/Other.hpp"

std::vector<std::string> get_nicknames(std::string arg)
{
    int i = 0;
    std::string nickname;
    std::vector<std::string> nicknames;
    while (arg[i] && arg[i] != ' ')
        i++;
    if (!arg[i])
        return (nicknames);
    i++;
    while (arg[i])
    {
        while (arg[i] && arg[i] != ' ' && arg[i]!=',')
        {
            nickname += arg[i];
            i++;
        }
        nicknames.push_back(nickname);
        nickname = "";
        if (!arg[i] || isspace(arg[i]))
            break;        
        i++;
    }
    return (nicknames);
}

std::string get_comment(std::string arg)
{

    std::istringstream iss(arg);
    std::string channel_name, user;
    
    iss >> channel_name >> user;
    
    std::string comment;
    std::getline(iss, comment);

    if (!comment.empty() && comment[0] == ' ')
        comment = comment.substr(1);
    if (!comment.empty() && comment[0] == ':')
        comment = comment.substr(1);
    return (comment);
}

bool is_good_channel_mask(std::string channel)
{
    if (channel.empty())
        return (false);
    if (!(channel[0] == '#' || channel[0] == '&'))
    {
        return (false);
    }
    for (int i = 1; channel[i]; i++)
    {
        if (channel[i] == ',' || channel[i] == ' '|| channel[i] == '\r'|| channel[i] == '\n')
            return (false);
    }
    return (true);
}

void Commands::KICK(Server *server, int fd, std::string arg)
{
    std::vector<std::string> channel_names;
    std::vector<std::string> nicknames;
    std::string comment;
    std::string channel_name;
    Client *client = server->getClient(fd);

    channel_names = get_channel_names(arg);
    nicknames = get_nicknames(arg);
    comment = get_comment(arg);
    if (channel_names.size() == 0 || nicknames.size() == 0 || (channel_names.size() > 1  && channel_names.size() != nicknames.size()))
    {
        server->sendMessage(ERR_NEEDMOREPARAMS(client->getNickname(), "KICK"), fd);
        return ;
    }
    for (size_t i = 0; i < nicknames.size(); i++)
    {
        if (channel_names.size() == 1)
            channel_name = channel_names[0];
        else
            channel_name = channel_names[i];
        // std::map<std::string, Channel*>::iterator it = server->getChannels().find(channel_name);
        // Channel *channel = it->second;
        Channel *channel = server->getChannel(channel_name);
        if (!is_good_channel_mask(channel_name))
            server->sendMessage(ERR_BADCHANMASK(channel_name, client->getNickname()), fd);
        // else if (it == server->getChannels().end())
        else if (!channel)
            server->sendMessage(ERR_NOSUCHCHANNEL(client->getNickname(), channel_name), fd);
        else if (!channel->isClient(fd))
            server->sendMessage(ERR_NOTONCHANNEL(client->getNickname(), channel_name), fd);
        else if(!channel->isOperator(fd))
            server->sendMessage(ERR_CHANOPRIVSNEEDED(client->getNickname(), channel_name), fd);
        // else if(!server->isClientIsInServer(nicknames[i]))
        //     server->sendMessage(client, ERR_NOSUCHNICK(client->getNickname(), nicknames[i]));
        else if(!channel->isClient(nicknames[i]))
            server->sendMessage(ERR_USERNOTINCHANNEL(nicknames[i], channel_name), fd);
        else 
        {
            channel->broadcast(RPL_KICK(client->getNickname(), client->getUsername(), channel_name, nicknames[i], comment), fd);
            channel->delUser(nicknames[i]);
        }
    }
}