#include "Channel.hpp"
#include "error.hpp"
#include "Server.hpp"

std::string	list_nick_channel(Channel& chan, Server& serv)
{
	std::string	nicknames;
	std::map<int, e_privilege>&	clis = chan.getClients();

	for (std::map<int, e_privilege>::iterator it = clis.begin(); it != clis.end(); ++it)
	{
		nicknames = nicknames + serv.findClient(it->first)->getNick() + " ";
	}
	return (nicknames);
}

void	actualise_name_reply(Channel& chan, Server& serv, Client& cli)
{
	std::map<int, e_privilege>&	clients = chan.getClients();

	for (std::map<int, e_privilege>::iterator it = clients.begin(); it != clients.end(); ++it)
	{
		if (it->second != INVITED)
			send_message(RPL_NAMEREPLY(cli.getNick(), chan.get_name(), list_nick_channel(chan, serv).c_str()), it->first);
	}
}

void Channel::joinChannel(Client& client, e_privilege privilege, std::string passwords, Server& serv)
{
	std::map <int, e_privilege > :: iterator it = this->clients.find(client.getFd());

	if (it != this->clients.end() && it->second != INVITED)
	{
		send_message(ERR_USERONCHANNEL(client.getNick(), this->name), client.getFd());
		return;
	}
	
    if (size() >= user_limit && user_limit != -1)
	{
		send_message(ERR_CHANNELISFULL(CLIENT(client.getNick(), client.getUser()), this->name), client.getFd());
		return ;
	}

	if (!this->password.empty())
	{
		if(this->password != passwords)
		{
			send_message(ERR_BADCHANNELKEY(CLIENT(client.getNick(), client.getUser()), this->name), client.getFd());
			return ;
		}
	}
	if (this->invite_only == true)
	{
		std::map <int, e_privilege > :: iterator it = this->clients.find(client.getFd());
		if(it == this->clients.end())
		{
			send_message(ERR_INVITEONLYCHAN(CLIENT(client.getNick(), client.getUser()), this->name), client.getFd());
			return ;
		}
	}
	if(it != clients.end())
		it->second = USER;
	else
		clients.insert(std::pair<int, e_privilege>(client.getFd(), privilege));

	send_message(RPL_JOIN(CLIENT(client.getNick(), client.getUser()), this->name), client.getFd());
	send_message(RPL_TOPIC(CLIENT(client.getNick(), client.getUser()), this->name, this->topic), client.getFd());
	actualise_name_reply(*this, serv, client);
}
