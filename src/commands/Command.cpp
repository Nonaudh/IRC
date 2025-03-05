#include "Command.hpp"
#include "QuitCommand.hpp"

Command::Command() {}

Command::Command(int socketFd, std::string command, std::vector <std::string> params)
	:socketFd(socketFd), command(command), params(params) {

}

Command::Command(const Command &copy) {
	*this = copy;
}

Command &Command::operator=(const Command &copy) {
	this->socketFd = copy.socketFd;
	this->command = copy.command;
	this->params = copy.params;

	return *this;
}

Command::~Command() {

}

int Command::getSocket() {
	return this->socketFd;
}

std::string Command::getName() {
	return this->command;
}

std::vector <std::string> Command::getParams() {
	return this->params;
}

void Command::execute() {
	if (this->command == "QUIT" || this->command == "quit")
		QuitCommand(socketFd, command, params).action();
}
