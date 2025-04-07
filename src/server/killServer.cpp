#include "Server.hpp"
#include "error.hpp"

int	find_clientFd_nickname(std::vector<Client>& clis, std::string nickname)
{
	std::vector<Client>::iterator	it;

	for (it = clis.begin(); it != clis.end() && it->getNick() != nickname; it++)
		;
	if (it != clis.end())
		return (it->getFd());
	return (-1);
}

void	Server::killFromServer(std::string nickname, std::string reason, int caller)
{
	int	fd = find_clientFd_nickname(this->getClient(), nickname);
	if (fd == -1)
	{
		send_message(ERR_NOSUCHNICK(std::string("client"), nickname), caller);
		return ;
	}
	if (!reason.empty())
	{
		send_message("You have been kicked from the server because ", fd);
		send_message(reason.c_str(), fd);
		send_message("\r\n", fd);
	}
	close(fd);
	this->eraseClient(fd);
	this->erasePoll(fd);
	// erase from all chanells too
}
