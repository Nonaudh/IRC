#include <Command.hpp>

// Command: KICK
// Parameters: <channel> <user> [<comment>]

// The KICK command can be  used  to  forcibly  remove  a  user  from  a
// channel.   It  'kicks  them  out'  of the channel (forced PART).

// Only a channel operator may kick another user out of a  channel.
// Each  server that  receives  a KICK message checks that it is valid
// (ie the sender is actually a  channel  operator)  before  removing
// the  victim  from  the channel.

// Numeric Replies:


int	checkKickCommand(Server& server, Client& cli, std::vector<std::string>& params)
{
	if (params.size() < 2)
	{
		send_message(ERR_NEEDMOREPARAMS(CLIENT(cli.getNick(), cli.getUser()), std::string("KICK")), cli.getFd());
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

	if (it2->second != ADMIN)
	{
		send_message(ERR_CHANOPRIVSNEEDED(CLIENT(cli.getNick(), cli.getUser()),  params[0]), cli.getFd());
		return (1);
	}
	return (0);
}

void	send_part_rply_to_channel(Channel& chan, Client& cli)
{
	std::map<int, e_privilege>::iterator it;

	for (it = chan.getClients().begin(); it != chan.getClients().end(); ++it)
		send_message(RPL_PART(CLIENT(cli.getNick(), cli.getUser()), chan.get_name()), it->first);
}

void Command::kickCommand()
{
    if (checkKickCommand(this->server, this->client, this->params))
        return ;

    Channel& chan = server.getChannels().find(params[0])->second;

    int fd_to_kick = this->server.findClientFd(params[1]);
    if (fd_to_kick == -1)
        return ;

    std::map<int, e_privilege>::iterator it = chan.getClients().find(fd_to_kick);
    if (it == chan.getClients().end())
        return ;

    chan.getClients().erase(it);
    send_message(RPL_KICK(CLIENT(client.getNick(), client.getUser()), params[0], params[1]), fd_to_kick);
	send_part_rply_to_channel(chan, *this->server.findClient(fd_to_kick));
}
