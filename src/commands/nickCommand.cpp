#include "Command.hpp"

bool	nickname_not_free(std::string& nick, std::vector<Client>& clients)
{
	std::vector<Client>::iterator it ;

	for (it = clients.begin(); it != clients.end() && it->getNick() != nick; ++it)
		;

	if (it != clients.end())
		return (true);
	return (false);
}

void	send_message(std::string str, int fd)
{
	send(fd, str.c_str(), str.length(), 0);
}

void	Command::nickCommand(void)
{
	if (this->params.empty())
	{
		send_message(ERR_NONICKNAMEGIVEN(this->client.getNick(), this->params[0]), this->client.getFd());
		return ;
	}

	if (nickname_not_free(this->params[0], this->server.getClient()))
	{
		send_message(ERR_NICKNAMEINUSE(this->client.getNick(), this->params[0]), this->client.getFd());
		return ;
	}
	
	send_message(RPL_NICK(this->client.getNick(), params[0]), this->getClient().getFd());
	this->client.setNick(this->params[0]);
}
