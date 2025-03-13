#include "Command.hpp"

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



int	checkModeCommand(Server& server, Client& cli, std::vector<std::string>& params)
{
	std::map<std::string, Channel >& chs = server.getChannels();

	if (params.empty())
	{
		send_message(ERR_NEEDMOREPARAMS("MODE"), cli.getFd());
		return (1);
	}
	if (chs.find(params[0]) == chs.end())
	{
		send_message(ERR_NOSUCHCHANNEL(params[0]), cli.getFd());
		return (1);
	}

}

void	Command::modeCommand(void)
{
	if (checkModeCommand(server, client, params))
		return ;
	std::string str;
}