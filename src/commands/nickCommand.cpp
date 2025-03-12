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

void	error_irc(const char *str, int fd)
{
	send(fd, str, strlen(str), 0);
}

void	Command::nickCommand(void)
{
	if (this->params.empty())
	{
		error_irc(ERR_NONICKNAMEGIVEN, this->client.getFd());
		return ;
	}

	if (nickname_not_free(this->params[0], this->server.getClient()))
	{
		error_irc(ERR_NICKNAMEINUSE(this->params[0].c_str()), this->client.getFd());
		return ;
	}
	this->client.setNick(this->params[0]);
}
