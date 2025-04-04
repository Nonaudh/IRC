#include "Command.hpp"

void Command::passCommand() {
	if (this->params.empty())
	{
		send_message(ERR_NEEDMOREPARAMS(CLIENT(client.getNick(), client.getUser()), "PASS"), this->client.getFd());
		return ;
	}

	if (!getServer().checkPassword(params[0])) {
		send_message(ERR_PASSWDMISMATCH(CLIENT(client.getNick(), client.getUser())), this->client.getFd());
		return;
	}

	if (client.getAuthen() >= PASSWORD) {
		send_message(ERR_ALREADYREGISTRED(CLIENT(client.getNick(), client.getUser())), this->client.getFd());
		return;
	}

	if (client.getAuthen() == NONE)
		client.Authen(PASSWORD);

	send_message("Password accepted\r\n", this->client.getFd());
	std::cout << this->client.getFd() << " has entered the correct password" << std::endl;
}
