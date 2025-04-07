#include "Command.hpp"

#include <iterator>

std::vector<std::string> ::const_iterator searchMdp(int i, std::string search, std::vector <std::string> params)
{
	std::vector<std::string> :: const_iterator const_it = std::find(params.begin(), params.end(), search);
	for(int t = 0; t != i; ++t)
		const_it++;
	return(const_it);
}

void Command::joinCommand()
{
	if (this->client.getAuthen() < CONNECT)
	{
		send_message(ERR_NOTREGISTERED(), this->client.getFd());
		return ;
	}
	
	if (params.empty())
	{
		send_message(ERR_NEEDMOREPARAMS(CLIENT(client.getNick(), client.getUser()), "JOIN"), client.getFd());
		return;
	}
	std::map<std::string, Channel>& channels = this->getServer().getChannels();

	std::vector <std::string> params = getParams();

	int searchNbrChannel = searchNbrChannels(this->params);

	int  searchMdpChannel = getParams().size()- searchNbrChannel;

	std::vector <std::string> ::const_iterator const_it;
	for( const_it= params.begin(); const_it != params.end() - searchMdpChannel;++const_it)
	{
		std::vector <std::string>::const_iterator copie = const_it;
		std::map<std::string,Channel>::iterator it = channels.find(*const_it);
		if (it == channels.end())
		{
			if (std::distance(static_cast<std::vector<std::string>::const_iterator>(params.begin()), const_it)+ searchNbrChannel < (int)params.size()&& searchMdpChannel != 0)
				channels.insert(std::pair<std::string, Channel>(*const_it, Channel(client.getFd(), *const_it,  *(searchMdp((searchNbrChannel), *copie, params)))));
			else
				channels.insert(std::pair<std::string, Channel>(*const_it, Channel(client.getFd(), *const_it, "")));
			send_message(RPL_JOIN(CLIENT(client.getNick(), client.getUser()), *const_it), client.getFd());
			send_message(RPL_NAMEREPLY(client.getNick(), *const_it, client.getNick()), client.getFd());
		}
		else
		{
			if (std::distance(static_cast<std::vector<std::string>::const_iterator>(params.begin()), const_it)+ searchNbrChannel < (int)params.size()&& searchMdpChannel != 0)
				 it->second.joinChannel(client, USER,  *(searchMdp(searchNbrChannel, *copie, params)), this->getServer());
			else
				it->second.joinChannel(client, USER,  "", this->getServer());
		}
	}
}
