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
		send_message(ERR_NONICKNAMEGIVEN(this->client.getNick(), ""), this->client.getFd());
		return ;
	}

	if (nickname_not_free(this->params[0], this->server.getClient()))
	{
		send_message(ERR_NICKNAMEINUSE(this->client.getNick(), this->params[0]), this->client.getFd());
		return ;
	}

	std::map<std::string, Channel>& channels = this->getServer().getChannels();

	for (std::map<std::string, Channel>::iterator it = channels.begin(); it != channels.end(); ++it)
	{
		if (it->second.getClients().find(this->client.getFd()) != it->second.getClients().end())
		{
			for (std::map<int, e_privilege>::iterator it2 = it->second.getClients().begin(); it2 != it->second.getClients().end(); ++it2)
			{
				send_message(RPL_NICK(this->client.getNick(), this->params[0]), it2->first);
			}
			it->second.getClients().erase(this->client.getFd());
		}
	}

	this->client.setNick(this->params[0]);
}
