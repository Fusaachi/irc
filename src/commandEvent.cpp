#include "../include/Server.hpp"
#include "../include/Commands.hpp"

Commands::Commands(){}

void Commands::execute_commands(Server *server, int fd)
{
	std::string test = "test";
	std::string tableCommands[12] = {"INVITE", "JOIN", "KICK", "MODE", "NICK", "PART", "PASS", "PING", "PRIVMSG", "QUIT", "TOPIC", "USER"};
	static bool (Commands::*table[12])(Server*, int, std::string) = {&Commands::INVITE, &Commands::JOIN, &Commands::KICK, &Commands::MODE, &Commands::NICK, &Commands::PART, &Commands::PASS, &Commands::PING, &Commands::PRIVMG, &Commands::QUIT, &Commands::TOPIC, &Commands::USER};

}