#include "QuitCommand.hpp"

QuitCommand::QuitCommand() : Command(){

}

QuitCommand::QuitCommand(Server server, Client client, std::string command, std::vector<std::string> params)
	: Command(server, client, command, params) {

}

QuitCommand::QuitCommand(const QuitCommand &copy) : Command(copy) {
	*this = copy;
}


QuitCommand &QuitCommand::operator=(const QuitCommand &copy) {
	if (this != &copy)
		*this = copy;
	return *this;
}

QuitCommand::~QuitCommand() {

}

void QuitCommand::action() {
	std::cout << "QuitCommand" << std::endl;

	std::cout << "SocketFd: " << getClient().getFd() << std::endl;
	std::cout << "Command: " << getName() << std::endl;
	std::cout << "Args: ";
	for (unsigned long i = 0; i < getParams().size(); ++i) {
		std::cout << getParams()[i];
	}
	std::cout << std::endl;
}