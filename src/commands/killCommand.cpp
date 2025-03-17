# include "Command.hpp"

void	Command::killCommand(void)
{
	if (this->client.getAuthen() != OP)
	{
		send_message(ERR_NOPRIVILEGES, this->client.getFd());
		return ;
	}
	switch (this->params.size())
	{
		case 0:
			send_message(ERR_NEEDMOREPARAMS("KILL"), this->client.getFd());
			break;
		
		case 1:
			this->server.killFromServer(params[0], "", this->client.getFd());
			break;
		
		default:
			this->server.killFromServer(params[0], params[1], this->client.getFd());
	}
}
