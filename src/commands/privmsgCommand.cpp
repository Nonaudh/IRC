#include "Command.hpp"
#include <sys/types.h>
#include <sys/socket.h>

void sendMessageAllPeople(std::vector<std::string> params, Client& client, std::map<int, e_privilege> clients)
{
	std::string message;
	for (std::map <int, e_privilege> ::iterator it = clients.begin(); it != clients.end(); ++it)
	{
		if (it->first != client.getFd() && it->second != INVITED)
		{
			message = PRIVMSG(CLIENT(client.getNick(), client.getUser()), params[0], params[1]);
			send_message(message, it->first);
		}
	}
}

bool clientInChannel(int clientFd,std::map<int, e_privilege> channel)
{
    std::map<int, e_privilege>::iterator    it = channel.find(clientFd);
    if (it != channel.end() && it->second != INVITED)
            return (true);
    return (false);
}

void sendMessageToChannel(std::map<std::string, Channel>& channels, std::vector<std::string> params, Client& client)
{
    std::map <std::string, Channel> :: iterator it = channels.find(params[0]);
    if (it != channels.end() && clientInChannel(client.getFd(),it->second.getClients()))
    {
        sendMessageAllPeople(params, client, it->second.getClients());
		return;
    }
	if (it == channels.end())
		send_message(ERR_NOSUCHCHANNEL(params[0]), client.getFd());
	else
		send_message(ERR_NOTONCHANNEL(CLIENT(client.getNick(), client.getUser()), params[0]), client.getFd());
}

void	sendMessageToNickname(Server& server, std::vector<std::string> params, Client& client)
{
	std::vector<Client>::iterator	it;

	for (it = server.getClient().begin(); it != server.getClient().end() && it->getNick() != params[0]; ++it)
		;
	if (it == server.getClient().end())
		send_message(ERR_NOSUCHNICK(CLIENT(client.getNick(), client.getUser()), params[0]), client.getFd());
	else
	{
		std::string message = PRIVMSG(CLIENT(client.getNick(), client.getUser()), params[0], params[1]);
		send_message(message, it->getFd());
	}
}


void Command::privmsgCommand()
{
	if (this->client.getAuthen() < CONNECT)
	{
		send_message(ERR_NOTREGISTERED(), this->client.getFd());
		return ;
	}

	if (params.size() < 2)
	{
		send_message(ERR_NEEDMOREPARAMS(CLIENT(client.getNick(), client.getUser()), "PRIVMSG"), client.getFd());
		return ;
	}
	if (params[1][0] != ':')
	{
		send_message(ERR_NOTEXTTOSEND(CLIENT(client.getNick(), client.getUser())), client.getFd());
		return ;
	}

	params[1].erase(params[1].begin());

	if(params[0][0] == '#' || params[0][0] == '&')
		sendMessageToChannel(this->server.getChannels(), this->getParams(), this->client);
	else 
		sendMessageToNickname(this->server, this->getParams(), this->client);
}
