#include "Command.hpp"

#include <sys/socket.h>

Command::Command(Server &server, Client &client, std::string command, std::vector <std::string> params)
	: server(server), client(client), command(command), params(params) {
}

Command::~Command() {

}

Server& Command::getServer() {
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

void Command::executeNotAuth() {
	std::string	cmd_bef_pass[] = {"CAP","NICK","USER","PASS"};

	int	i;
	for (i = 0; i < 4 && command != cmd_bef_pass[i]; ++i)
		;

	switch (i) {
		case (0):
			break ;
		case (1):
			// std::cout << "1" << std::endl;
			nickCommand();
			break ;
		case (2):
			// std::cout << "2" << std::endl;
			userCommand();
			break ;
		case (3):
			// std::cout << "3" << std::endl;
			passCommand();
			break ;
		default:
			std::cout << "4" << std::endl;
			send_message(ERR_NOTREGISTERED(), this->client.getFd());
			break;
	}
}

void Command::execute() {
	std::string	cmd_available[] = {"KILL", "QUIT", "JOIN",
	  "NICK", "PRIVMSG", "MODE", "TOPIC", "KICK",
	  "INVITE", "NOTICE", "PART", ""};

	int	i;
	int max;

	for (max = 0; !cmd_available[max].empty(); ++max)
		;
	for (i = 0; i < max && command != cmd_available[i]; ++i)
		;

	switch (i)
	{
		case (KILL):
			killCommand();
			break ;
		case (QUIT):
			quitCommand();
			break ;
		case (JOIN):
			joinCommand();
			break ;
		case (NICK_CMD) :
			nickCommand();
			break ;
		case (PRIVMSG_CMD):
			privmsgCommand();
			break ;
		case (MODE) :
			modeCommand();
			break ;
		case(TOPIC):
			topicCommand();
			break ;
		case(KICK):
			kickCommand();
			break ;
		case(INVITE):
			inviteCommand();
			break ;
		case (NOTICE_CMD):
			noticeCommand();
			break;
		case (PART):
			partCommand();
			break;
		default:
			std::cout << "Unknow cmd : " << command << std::endl;
			break ;
	}
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

