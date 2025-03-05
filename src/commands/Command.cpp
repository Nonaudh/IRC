#include "Command.hpp"
#include "QuitCommand.hpp"

Command::Command() : client(Client(0)) {
}

Command::Command(Server server, Client client, std::string command, std::vector <std::string> params)
	: server(server), client(client), command(command), params(params) {
}

Command::Command(const Command &copy) : client(Client(0)) {
	*this = copy;
}

Command &Command::operator=(const Command &copy) {
	if (this != &copy) {
		server = copy.server;
		client = copy.client;
		command = copy.command;
		params = copy.params;
	}
	return *this;
}

Command::~Command() {

}

Server Command::getServer() {
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
		QuitCommand(server, client, command, params).action();
}

