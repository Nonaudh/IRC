#include "Command.hpp"

int	Command::find_clientFd_nickname(void)
{
	std::vector<Client>::iterator	it;
	std::vector<Client>& clis = this->getServer().getClient();

	for (it = clis.begin(); it != clis.end() && it->getNick() != getParams()[0]; it++)
		;
	return (it->getFd());
}

void	Command::killCommand(void) // i think this is wrong :/
{
	//this->client should be op to perform killCommand
	int	fd = find_clientFd_nickname();

	close(fd);
	this->server.eraseClient(fd);
	this->server.erasePoll(fd);

	// erase from all chanells too
}
