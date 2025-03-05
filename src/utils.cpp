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

std::vector<std::string> split(char *str, const char *sep) {
	std::vector<std::string> ret;

	if (!str || !sep) return ret;

	char *token = strtok(str, sep);

	size_t len = strlen(str);
	if (len > 0 && str[len - 1] == '\n') {
		str[len - 1] = '\0';
	}

	while (token != NULL) {
		ret.push_back(std::string(token));
		token = strtok(NULL, sep);
	}

	return ret;
}

Command Server::parseCommand(int socketFd, char *buff) {
	Command command;
	std::vector<std::string> splitted;
	std::string command_name;

	splitted = split(buff, " ");

	if (splitted.empty())
		return command;

	command_name = splitted[0];
	splitted.erase(splitted.begin());

	return Command(socketFd, command_name, splitted);
}