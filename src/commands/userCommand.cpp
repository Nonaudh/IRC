#include "Command.hpp"

void	Command::userCommand(void)
{
	if (this->params.empty())
	{
		send_message(ERR_NEEDMOREPARAMS(CLIENT(client.getNick(), client.getUser()), "USER"), this->client.getFd());
		return ;
	}

	if (!client.getUser().empty())
		send_message(ERR_ALREADYREGISTRED(CLIENT(client.getNick(), client.getUser())), this->client.getFd());

	client.setUser(params[0]);
}
