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
		bool PART(Server *server, int fd, std::string arg);
		bool PASS(Server *server, int fd, std::string password);
		bool PING(Server *server, int fd, std::string user);
		bool PRIVMG(Server *server, int fd, std::string user);
		bool QUIT(Server *server, int fd, std::string reason);
		bool TOPIC(Server *server, int fd, std::string user);
		bool USER(Server *server, int fd, std::string user);

	public :
		Commands();
		void execute_commands(Server *server, int fd);
};
