#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <vector>
#include <iostream>
#include "Client.hpp"
#include "Server.hpp"
# include <map>

enum	e_cmd
{
	QUIT,
	JOIN,
	NICK,
};

class Command {
public:
	// Command();
	Command(Server& server, Client &client, std::string command, std::vector<std::string> params);
	//Command(const Command &copy);
	//Command &operator=(const Command &copy);
	virtual ~Command();

	Server& getServer();
	Client getClient();
	std::string getName();
	std::vector<std::string> getParams();

	void execute();
private:
	Server& server;
	Client& client;
	std::string command;
	std::vector<std::string> params;

	void	quitCommand(void);
	void	joinCommand(void);
	void	nickCommand(void);
	
};

#endif