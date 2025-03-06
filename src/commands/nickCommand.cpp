#include "Command.hpp"

bool	nickname_not_free(std::string& cmd, std::vector<Client>& clients)
{
	std::vector<Client>::iterator it ;

	for (it = clients.begin(); it != clients.end() && it->getNick() != cmd; ++it)
		;
	
	if (it != clients.end())
		return (true);
	return (false);
}

void	Command::nickCommand(void)
{
	if (nickname_not_free(this->command, this->server.getClient()))
		return ;
	
	this->client.setNick(this->params[0]);
}
