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
	std::string	cmd_available[] = {"PASS", "USER", "KILL", "JOIN",
	  "NICK", "PRIVMSG", "MODE", "TOPIC", "KICK",
	  "INVITE", "NOTICE", "PART", ""};

	int	i;

	for (i = 0; !cmd_available[i].empty() && command != cmd_available[i]; ++i)
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
			break ;
	}

	if (this->client.getAuthen() < CONNECT)
		check_authen(this->client);
}
