#ifndef ACOMMAND_HPP
#define ACOMMAND_HPP

#include <string>
#include <vector>
#include <iostream>
#include "Client.hpp"
#include "Server.hpp"

class Command {
public:
	Command(Server server, Client &client, std::string command, std::vector<std::string> params);
	Command &operator=(const Command &copy);
	virtual ~Command();

	Server getServer();
	Client& getClient();
	std::string getName();
	std::vector<std::string> getParams();

	void execute();
private:
	Server server;
	Client& client;
	std::string command;
	std::vector<std::string> params;

	void quitCommand();
	void passCommand();
};

#endif