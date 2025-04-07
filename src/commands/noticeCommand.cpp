#include "Command.hpp"
#include <sys/socket.h>

void	send(Server& server, std::vector<std::string> params, Client& client)
{
	std::vector<Client>::iterator	it;

	for (it = server.getClient().begin(); it != server.getClient().end() && it->getNick() != params[0]; ++it)
		;
	if (it != server.getClient().end()) {
		std::string message = NOTICE(CLIENT(client.getNick(), client.getUser()), params[0], params[1]);
		send(it->getFd(), message.c_str(), message.size(), 0);
	}
}

void Command::noticeCommand()
{
	if (this->client.getAuthen() < CONNECT)
	{
		send_message(ERR_NOTREGISTERED(), this->client.getFd());
		return ;
	}
	
	if (params.size() < 2)
		return ;

	if (params[1][0] != ':')
		return;

	params[1].erase(params[1].begin());
	if(params[0][0] != '#' && params[0][0] != '&')
		send(this->server, this->getParams(), this->client);

}
