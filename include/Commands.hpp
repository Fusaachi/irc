#include "Server.hpp"


class Server;
class Client;

class Commands
{
	private :

		bool INVITE(Server *server, int fd, std::string user);
		bool JOIN(Server *server, int fd, std::string user);
		bool KICK(Server *server, int fd, std::string user);
		bool MODE(Server *server, int fd, std::string user);
		bool NICK(Server *server, int fd, std::string nick);
		bool PART(Server *server, int fd, std::string const &arg);
		bool PASS(Server *server, int fd, std::string password);
		bool PING();
		bool PRIVMG();
		bool QUIT(Server *server, int fd, std::string reason);
		bool TOPIC();
		bool USER(Server *server, int fd, std::string user);

	public :
		Commands();
		void execute_commands(Server *server, int fd);
};
