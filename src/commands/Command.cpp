#include <sys/socket.h>
#include "Command.hpp"

Command::Command(Server server, Client &client, std::string command, std::vector <std::string> params)
	: server(server), client(client), command(command), params(params) {
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

Client& Command::getClient() {
	return client;
}

std::string Command::getName() {
	return this->command;
}

std::vector <std::string> Command::getParams() {
	return this->params;
}

void Command::execute() {
	if (!client.getAuthen()) {
		if (this->command == "PASS")
			this->passCommand();
		return;
	}

	if (this->command == "JOIN")
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

void Command::passCommand() {
	std::cout << "PassCommand" << std::endl;

	std::cout << "SocketFd: " << getClient().getFd() << std::endl;
	std::cout << "Command: " << getName() << std::endl;
	std::cout << "Args: ";
	for (unsigned long i = 0; i < getParams().size(); ++i) {
		std::cout << getParams()[i];
	}
	std::cout << std::endl;

	int socketFd = client.getFd();

	if (params.size() != 1) {
		send(socketFd, "Usage: PASS <password>\n", 23, 0);
		return;
	}

	if (!getServer().checkPassword(params[0])) {
		send(socketFd, "Wrong password, try again\n", 26, 0);
		return;
	}

	client.Authen();

	send(socketFd, "You're now connected\n", 22, 0);
	std::cout << socketFd << " is now connected to the server" << std::endl;
}
