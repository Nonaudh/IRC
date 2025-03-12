#include "Server.hpp"

int	find_clientFd_nickname(std::vector<Client>& clis, std::string nickname)
{
	std::vector<Client>::iterator	it;

	for (it = clis.begin(); it != clis.end() && it->getNick() != nickname; it++)
		;
	if (it != clis.end())
		return (it->getFd());
	return (-1);
}

void	Server::killFromServer(std::string nickname, std::string reason) // i think this is wrong :/
{
	//this->client should be op to perform killCommand
	int	fd = find_clientFd_nickname(this->getClient(), nickname);
	if (fd == -1)
	{
		std::cout << "Invalid KillCommand used for nickname : " << nickname << std::endl;
		return ;
	}

	send(fd, reason.c_str(), reason.length(), 0);
	close(fd);
	this->eraseClient(fd);
	this->erasePoll(fd);
	// erase from all chanells too
}
