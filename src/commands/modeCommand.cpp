#include "Command.hpp"
#include <sstream>

// MODE - Change the channel’s mode:

// Parameters: <channel> {[+|-]|o|p|s|i|t|n|b|v} [<limit>] [<user>]
// [<ban mask>]

// · i: Set/remove Invite-only channel
// · t: Set/remove the restrictions of the TOPIC command to channel operators
// · k: Set/remove the channel key (password)
// · o: Give/take channel operator privilege
// · l: Set/remove the user limit to channel

// ERR_NEEDMOREPARAMS              RPL_CHANNELMODEIS
// ERR_CHANOPRIVSNEEDED            ERR_NOSUCHNICK
// ERR_NOTONCHANNEL                ERR_KEYSET
// RPL_BANLIST                     RPL_ENDOFBANLIST
// ERR_UNKNOWNMODE                 ERR_NOSUCHCHANNEL

// RPL_CHANNELMODEIS
// "<channel> <mode> <mode params>"  TO DO !

int	int_to_string(std::string& str)
{
	std::istringstream	stream(str);
	int	nb;

	stream >> nb;
	std::cout << "new_limit : " << nb << std::endl; // to check
	return (nb); // what ?
}

int	checkModeCommand(Server& server, Client& cli, std::vector<std::string>& params)
{
	std::map<std::string, Channel >& chs = server.getChannels();

	if (params.empty())
	{
		send_message(ERR_NEEDMOREPARAMS(CLIENT(cli.getNick(), cli.getUser()), std::string("MODE")), cli.getFd());
		return (1);
	}

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

	if (params.size() == 1)
	{
		send_message(RPL_CHANNELMODEIS(cli.getNick(), it->second.get_name(), " " + it->second.getChannelModeReply()), cli.getFd());
		return (0);
	}

	if (it2->second != ADMIN)
	{
		send_message(ERR_CHANOPRIVSNEEDED(CLIENT(cli.getNick(), cli.getUser()),  params[0]), cli.getFd());
		return (1);
	}
	return (0);
}

int	not_a_mode(std::string& s1)
{
	std::string	mode = "itkol";

	if (s1[0] != '+' && s1[0] != '-')
		return (1);
	if (mode.find(s1[1]) == std::string::npos)
		return (1);
	return (0);
}

int	handle_mode_i(std::string& s1, Channel& chan)
{
	switch (s1[0])
	{
		case '+':
			chan.set_invite_only(true);
			break ;
		case '-':
			chan.set_invite_only(false);
			break ;
	}
	return (1);
}

int	handle_mode_t(std::string& s1, Channel& chan)
{
	switch (s1[0])
	{
		case '+':
			chan.set_topic_editable(true);
			break ;
		case '-':
			chan.set_topic_editable(false);
			break ;
	}
	return (1);
}

int	handle_mode_k(std::string& s1, std::string& s2, Channel& chan, Client& cli)
{
	switch (s1[0])
	{
		case '+':
			if (s2.empty())
			{
				send_message(ERR_NEEDMOREPARAMS(CLIENT(cli.getNick(), cli.getUser()), std::string("MODE +k")), cli.getFd());
				return (1);
			}
			chan.set_password(s2);
			return (2);
		case '-':
			chan.set_password("");
			return (1);
	}
	return (1);
}

int	handle_mode_o(std::string& s1, std::string& s2, Channel& chan, Client& cli, Server& server)
{
	std::map<int, e_privilege>& clients = chan.getClients();
	int	clientfd;
	int	fd = cli.getFd();

	switch (s1[0])
	{
		case '+':
			if (s2.empty())
			{
				send_message(ERR_NEEDMOREPARAMS(CLIENT(cli.getNick(), cli.getUser()), std::string("MODE +o")), cli.getFd());
				return (1);
			}
			clientfd = server.findClientFd(s2);
			if (clientfd == fd)
				return (2);
			if (clients.find(clientfd) == clients.end())
			{
				send_message(ERR_NOSUCHNICK(CLIENT(cli.getNick(), cli.getUser()), std::string(s2)), fd);
				return (2);
			}
			clients.find(clientfd)->second = ADMIN;
			return (2);
		
		case '-':
			if (s2.empty())
			{
				send_message(ERR_NEEDMOREPARAMS(CLIENT(cli.getNick(), cli.getUser()), std::string("MODE -o")), cli.getFd());
				return (1);
			}
			clientfd = server.findClientFd(s2);
			if (clients.find(clientfd) == clients.end())
			{
				send_message(ERR_NOSUCHNICK(CLIENT(cli.getNick(), cli.getUser()), std::string(s2)), fd);
				return (2);
			}
			clients.find(clientfd)->second = USER;
			return (2);
	}
	return (1);
}

int	handle_mode_l(std::string& s1, std::string& s2, Channel& chan, Client& cli)
{
	switch (s1[0])
	{
		case '+':
			if (s2.empty())
			{
				send_message(ERR_NEEDMOREPARAMS(CLIENT(cli.getNick(), cli.getUser()), std::string("MODE +l")), cli.getFd());
				return (1);
			}
			chan.set_user_limit(int_to_string(s2));
			return (2);

		case '-':
			chan.set_user_limit(-1);
			return (1);
	}
	return (1);
}

size_t	handle_mode(std::string& s1, std::string& s2, Channel& chan, Client& cli, Server& server)
{
	if (s1.size() != 2)
	{
		send_message(ERR_UNKNOWNMODE(CLIENT(cli.getNick(), cli.getUser()), s1), cli.getFd());
		return (1);
	}

	if (not_a_mode(s1))
	{
		send_message(ERR_UNKNOWNMODE(CLIENT(cli.getNick(), cli.getUser()), s1), cli.getFd());
		return (1);
	}

	switch (s1[1])
	{
		case 'i':
			return (handle_mode_i(s1, chan));
		case 't':
			return (handle_mode_t(s1, chan));
		case 'k':
			return (handle_mode_k(s1, s2, chan, cli));
		case 'o':
			return (handle_mode_o(s1, s2, chan, cli, server));
		case 'l':
			return (handle_mode_l(s1, s2, chan, cli));
	}
	return (1);
}

void	Command::modeCommand(void)
{
	if (this->client.getAuthen() < CONNECT)
	{
		send_message(ERR_NOTREGISTERED(), this->client.getFd());
		return ;
	}
	
	if (checkModeCommand(server, client, params))
		return ;

	size_t	i = 0;
	Channel& chan = server.getChannels().find(params[0])->second;

	std::vector<std::string>::iterator	it;
	for (it = params.begin() + 1; it != params.end(); it += i)
	{
		if (it + 1 != params.end())
			i = handle_mode(*it, *(it + 1), chan, client, server);
		else
		{
			std::string	empty = "";
			i = handle_mode(*it, empty, chan, client, server);
		}
	}
	chan.info(); //to erase
}
