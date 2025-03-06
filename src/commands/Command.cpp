#include "Command.hpp"

// Command::Command() : client(Client(0)) {
// }

Command::Command(Server &server, Client &client, std::string command, std::vector <std::string> params)
	: server(server), client(client), command(command), params(params) {
}

// Command::Command(const Command &copy) : client(Client(0)) {
// 	*this = copy;
// }

// Command &Command::operator=(const Command &copy) {
// 	if (this != &copy) {
// 		server = copy.server;
// 		client = copy.client;
// 		command = copy.command;
// 		params = copy.params;
// 	}
// 	return *this;
// }

Command::~Command() {

}

Server& Command::getServer() {
	return server;
}

Client Command::getClient() {
	return client;
}

std::string Command::getName() {
	return this->command;
}

std::vector <std::string> Command::getParams() {
	return this->params;
}

void Command::execute() {
	if (this->command == "QUIT" || this->command == "quit")
		this->quitCommand();
}

void Command::quitCommand() {
	std::cout << "QuitCommand" << std::endl;

	std::cout << "SocketFd: " << getClient().getFd() << std::endl;
	std::cout << "Command: " << getName() << std::endl;
	std::cout << "Args: ";
	for (unsigned long i = 0; i < getParams().size(); ++i) {
		std::cout << getParams()[i];
	}

	std::cout << std::endl;
}
