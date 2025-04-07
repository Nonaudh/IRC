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

// void Command::executeNotAuth() {
// 	std::string	cmd_bef_pass[] = {"CAP","NICK","USER","PASS"};

// 	int	i;
// 	for (i = 0; i < 4 && command != cmd_bef_pass[i]; ++i)
// 		;

// 	switch (i) {
// 		case (0):
// 			break ;
// 		case (1):
// 			nickCommand();
// 			break ;
// 		case (2):
// 			userCommand();
// 			break ;
// 		case (3):
// 			passCommand();
// 			break ;
// 		default:
// 			send_message(ERR_NOTREGISTERED(), this->client.getFd());
// 			break;
// 	}
// }

void	check_authen(Client& cli)
{
	if (cli.getAuthen() == PASSWORD &&
		!cli.getNick().empty() &&
		!cli.getUser().empty())
		{
			cli.Authen(CONNECT);
			send_message(RPL_WELCOME(cli.getNick()), cli.getFd());
			std::cout << cli.getFd() << " is now connected to the server" << std::endl;
		}
}

void Command::execute() 
{
	std::string	cmd_available[] = {"PASS", "USER", "KILL", "QUIT", "JOIN",
	  "NICK", "PRIVMSG", "MODE", "TOPIC", "KICK",
	  "INVITE", "NOTICE", "PART"};

	int	i;
	int max;

	
	for (max = 0; !cmd_available[max].empty(); ++max)
	;
	for (i = 0; i < max && command != cmd_available[i]; ++i)
	;
	
	switch (i)
	{
		case (PASS):
			passCommand();
			break ;
		case (USER_CMD):
			userCommand();
			break ;
		case (KILL):
			killCommand();
			break ;
		case (QUIT):
			quitCommand(); // ?
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

	if (this->client.getAuthen() < CONNECT)
		check_authen(this->client);
}

void Command::quitCommand() {

	if (this->client.getAuthen() < CONNECT)
	{
		send_message(ERR_NOTREGISTERED(), this->client.getFd());
		return ;
	}
	
	std::cout << "QuitCommand" << std::endl;

	std::cout << "SocketFd: " << getClient().getFd() << std::endl;
	std::cout << "Command: " << getName() << std::endl;
	std::cout << "Args: ";
	for (unsigned long i = 0; i < getParams().size(); ++i) {
		std::cout << getParams()[i];
	}

	std::cout << std::endl;
}

