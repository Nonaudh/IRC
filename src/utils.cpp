#include "irc.hpp"

void	Server::addToPoll(int socketFd)
{
	pollfd		newPoll;

	newPoll.fd = socketFd;
	newPoll.events = POLLIN;
	newPoll.revents = 0;

	pollfds.push_back(newPoll);
}

void	Server::erasePoll(int socketFd)
{
	std::vector<pollfd>::iterator	it;

	for (it = pollfds.begin(); it < pollfds.end() && it->fd != socketFd; ++it)
		;
	if (it != pollfds.end())
		pollfds.erase(it);
}

int	Server::setPortPassword(char **argv)
{
	port = atoi(argv[1]);
	//check port range
	password = argv[2];

	return (0);
}
