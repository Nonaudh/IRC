#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <vector>
#include <iostream>
#include "Client.hpp"
#include "Server.hpp"
#include <algorithm>    // std::find
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
	PART,
	TOPIC, 
	KICK,
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
	void	firstParamChannelCommand(int i);
	void	killCommand(void);
	void	modeCommand(void);
	void	executePartCommand(std::map<std::string, Channel>& channels, std::vector<std::string> params, int clientFd);
	std::vector<std::string>  searchAllChannel(std::vector<std::string> arg, int index);

};

void	send_message(const char *str, int fd);

#endif