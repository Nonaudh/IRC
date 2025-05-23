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
	if(port < 1024 || port > 65535)
		return(1);
	password = argv[2];

	return (0);
}

void	Server::addToClient(int socketFd)
{
	Client	cli(socketFd);

	clients.push_back(cli);
}

void	Server::eraseClient(int socketFd)
{
	std::vector<Client>::iterator	it;

	for (it = clients.begin(); it != clients.end() && it->getFd() != socketFd; ++it)
		;
	clients.erase(it);
}

std::vector<Client>::iterator	Server::findClient(int socketFd)
{
	std::vector<Client>::iterator	it;

	for (it = clients.begin(); it != clients.end() && socketFd != it->getFd(); ++it)
		;
	return (it);
}

int		Server::findClientFd(std::string nickname)
{
	std::vector<Client>::iterator	it;

	for (it = clients.begin(); it != clients.end() && nickname != it->getNick(); ++it)
		;
	if (it != clients.end())
		return (it->getFd());
	return (-1);
}

std::map<std::string, Channel>&	Server::getChannels(void)
{
	return (this->channels);
}

std::vector<Client>&	Server::getClient(void)
{
	return (this->clients);
}

void	Server::closeAllFd(void)
{
	for (std::vector<Client>::iterator it = this->clients.begin(); it != this->clients.end(); ++it)
		close (it->getFd());
	close(this->serSocketFd);
}

void	Server::signalHandler(int sig)
{
	(void)sig;

	std::cout << std::endl;
	Server::Signal = true;
}
