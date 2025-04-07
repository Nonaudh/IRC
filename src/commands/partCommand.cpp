#include <Command.hpp>

void leave(Client& client, Channel& chan)
{
	std::map<int, e_privilege>::iterator it = chan.getClients().find(client.getFd());

	if (it == chan.getClients().end())
	{
		send_message(ERR_NOTONCHANNEL(CLIENT(client.getNick(), client.getUser()), chan.get_name()), client.getFd());
		return ;
	}
	for (std::map<int, e_privilege>::iterator it = chan.getClients().begin(); it != chan.getClients().end(); ++it)
		send_message(RPL_PART(CLIENT(client.getNick(), client.getUser()), chan.get_name()), it->first);

	chan.getClients().erase(it);
}

void Command::partCommand() {

	if (this->client.getAuthen() < CONNECT)
	{
		send_message(ERR_NOTREGISTERED(), this->client.getFd());
		return ;
	}
	
	if(params.empty())
	{
		send_message(ERR_NEEDMOREPARAMS(CLIENT(client.getNick(), client.getUser()), "PART"), client.getFd());
		return;
	}

	int msg = 0;

	std::vector <std::string> params = getParams();

	if (params.back()[0] == ':')
	{
		msg = 1;
		params.back() = params.back().substr(1);
	}

	std::map<std::string, Channel>& channels = this->getServer().getChannels();

	for(std::vector <std::string> ::const_iterator const_it = params.begin(); const_it != params.end() - msg; ++const_it)
	{
		if (server.findChannel(*const_it))
			leave(client, channels[*const_it]);
		else
			send_message(ERR_NOSUCHCHANNEL(*const_it), client.getFd());
	}
}
