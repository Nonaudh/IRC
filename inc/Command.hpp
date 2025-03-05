#ifndef ACOMMAND_HPP
#define ACOMMAND_HPP

#include <string>
#include <vector>
#include <iostream>

class Command {
public:
	Command();
	Command(int socketFd, std::string command, std::vector<std::string> params);
	Command(const Command &copy);
	Command &operator=(const Command &copy);
	virtual ~Command();

	int getSocket();
	std::string getName();
	std::vector<std::string> getParams();

	void execute();
private:
	int socketFd;
	std::string command;
	std::vector<std::string> params;
};

#endif