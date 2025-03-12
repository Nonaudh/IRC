#include "Command.hpp"

void	Command::killCommand(void) // i think this is wrong :/
{
	//this->client should be op to perform killCommand
	return ;
	int	fd = this->client.getFd(); // not this->clients but params[0]

	close(fd);
	this->server.eraseClient(fd);
	this->server.erasePoll(fd);

	// erase from all chanells too
}
