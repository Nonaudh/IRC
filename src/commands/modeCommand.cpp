#include "Command.hpp"
#include "regex.h"

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

int	unknowMode(std::string param)
{
	int	err;
	regex_t	preg;
	const char	*str_regex =  "^[+-](o|p|s|i|t|n|b|v).*$";

	err = regcomp (&preg, str_regex, REG_NOSUB | REG_EXTENDED);
	if (err == 0)
	{
		int match;
		match = regexec(&preg, param.c_str(), 0, NULL, 0);
		regfree(&preg);
		if (match == 0)
			return (0);
	}
	return (1);
}

int	checkModeCommand(Server& server, Client& cli, std::vector<std::string>& params)
{
	std::map<std::string, Channel >& chs = server.getChannels();

	if (params.size() < 2)
	{
		send_message(ERR_NEEDMOREPARAMS("MODE"), cli.getFd());
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
		send_message(ERR_NOTONCHANNEL(params[0]), cli.getFd());
		return (1);
	}

	if (it->second.getMdfTopic() && it2->second != ADMIN)
	{
		send_message(ERR_CHANOPRIVSNEEDED(params[0]), cli.getFd());
		return (1);
	}

	// if (unknowMode(params[1])) fuck les regexs
	// {
	// 	send_message("Error regex\r\n", cli.getFd());
	// 	return (1);
	// }

	return (0);
}

void	Command::modeCommand(void)
{
	if (checkModeCommand(server, client, params))
		return ;
	std::string str;
}