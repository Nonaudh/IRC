#include "Command.hpp"

int	checkTopicCommand(Server& server, Client& cli, std::vector<std::string>& params)
{
	if (params.size() < 1 )
	{
		send_message(ERR_NEEDMOREPARAMS(CLIENT(cli.getNick(), cli.getUser()), std::string("TOPIC")), cli.getFd());
		return (1);
	}

	std::map<std::string, Channel >& chs = server.getChannels();
	std::map<std::string, Channel >::iterator	it = chs.find(params[0]);
	if (it == chs.end())
	{
		send_message(ERR_NOSUCHCHANNEL(params[0]), cli.getFd());
		return (1);
	}

	std::map<int, e_privilege >::iterator	it2 = it->second.getClients().find(cli.getFd()) ;
	if (it2 == it->second.getClients().end())
	{
		send_message(ERR_NOTONCHANNEL(CLIENT(cli.getNick(), cli.getUser()),  params[0]), cli.getFd());
		return (1);
	}    
	return (0);
}

void    Command::topicCommand(void)
{
	if (this->client.getAuthen() < CONNECT)
	{
		send_message(ERR_NOTREGISTERED(), this->client.getFd());
		return ;
	}

    if (checkTopicCommand(this->server, this->client, this->params))
    	return ;

    std::map<std::string, Channel >& chs = server.getChannels();
    std::map<std::string, Channel >::iterator	it = chs.find(params[0]);

    if(params.size() == 1)
    {
        if(it->second.get_topic().empty())
            send_message(RPL_NOTOPIC(CLIENT(this->client.getNick(), this->client.getUser()), params[0]), this->client.getFd());
        else
            send_message(RPL_SEETOPIC(CLIENT(this->client.getNick(), this->client.getUser()), params[0], it->second.get_topic()), this->client.getFd());
		return;
	}

	if (params[1][0] == ':')
		params[1].erase(params[1].begin());

	if (it->second.getClients().find(client.getFd())->second != ADMIN && !it->second.get_topic_editable() )
	{
		send_message(ERR_CHANOPRIVSNEEDED(CLIENT(this->client.getNick(), this->client.getUser()),  params[0]), client.getFd());
		return ;
	}
	it->second.set_topic(params[1]);

	if (it->second.getClients().find(this->client.getFd()) != it->second.getClients().end())
	{
		for (std::map<int, e_privilege>::iterator it2 = it->second.getClients().begin(); it2 != it->second.getClients().end(); ++it2)
			if (it2->first != this->client.getFd())
				send_message(RPL_TOPIC(CLIENT(this->client.getNick(), this->client.getUser()), params[0], it->second.get_topic()), it2->first);
	}
	send_message(RPL_TOPIC(CLIENT(this->client.getNick(), this->client.getUser()), params[0], it->second.get_topic()), this->client.getFd());
}
