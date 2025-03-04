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

void	Server::addToClient(int socketFd)
{
	Client	cli;

	cli.setFd(socketFd);

	clients.push_back(cli);
}

void	Server::eraseClient(int socketFd)
{
	std::vector<Client>::iterator	it;

	for (it = clients.begin(); it != clients.end() && it->getFd() != socketFd; ++it)
		;
	clients.erase(it);
}

Client&	Server::findClient(int socketFd)
{
	std::vector<Client>::iterator	it;

	for (it = clients.begin(); it != clients.end() && socketFd != it->getFd(); ++it)
		;
	return (*it);
}

int	Server::enterPassword(int socketFd, char *buff)
{
	if (buff != password + "\n")
	{
		send(socketFd, "Wrong password, try again\n", 26, 0);
		return (0);
	}
	else
		send(socketFd, "You're now connected\n", 22, 0);
	return (1);
}
