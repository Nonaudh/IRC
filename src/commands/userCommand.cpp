#include "Command.hpp"

void	Command::userCommand(void)
{
	if (this->params.empty())
	{
		send_message(ERR_NEEDMOREPARAMS(CLIENT(client.getNick(), client.getUser()), "USER"), this->client.getFd());
		return ;
	}

	if (client.getAuthen() < NICK)
		return;

	if (!client.getUser().empty())
		send_message(ERR_ALREADYREGISTRED(CLIENT(client.getNick(), client.getUser())), this->client.getFd());

	client.setUser(params[0]);
	client.Authen(CONNECT);

	send_message(RPL_WELCOME(client.getNick()), this->client.getFd());
	std::cout << this->getClient().getFd() << " is now connected to the server" << std::endl;
}
