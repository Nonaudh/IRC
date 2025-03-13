#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <vector>
#include <iostream>
#include "Client.hpp"
#include "Server.hpp"
# include <map>
# include "error.hpp"
# include <sys/types.h>
# include <sys/socket.h>
# include <cstring>
# include <unistd.h>

enum	e_cmd
{
	KILL,
	QUIT,
	JOIN,
	NICK,
	PRIVMSG,
	MODE,
};

class Command {
public:
	Command(Server& server, Client &client, std::string command, std::vector<std::string> params);
	virtual ~Command();

	Server& getServer();
	Client& getClient();
	std::string getName();
	std::vector<std::string> getParams();

	void execute();

private:
	Server& server;
	Client& client;
	std::string command;
	std::vector<std::string> params;

	void	passCommand(void);
	void	quitCommand(void);
	void	joinCommand(void);
	void	nickCommand(void);
	void	privmsgCommand(void);
	void	killCommand(void);
	void	modeCommand(void);
};

void	send_message(const char *str, int fd);

#endif