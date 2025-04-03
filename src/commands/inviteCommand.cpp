#include "Command.hpp"


int Command::not_a_user(std::string str)
{
    std::vector<Client>& clients = this->server.getClient();
    std::vector<Client>::iterator it;

    for (it = clients.begin(); it != clients.end() && str != it->getNick(); ++it)
        ;
    if (it == clients.end())
    {
        send_message(ERR_NOSUCHNICK(CLIENT(client.getNick(), client.getUser()), str), this->client.getFd());
        return (1);
    }
    return (0);
}

int Command::not_a_channel(std::string str)
{
    std::map<std::string, Channel>::iterator    it = this->server.getChannels().find(str);

    if (it == this->server.getChannels().end())
    {
        send_message(ERR_NOSUCHCHANNEL(str), this->client.getFd());
        return (1);
    }
    return (0);
}

int not_in_or_admin_channel(Client& client, std::string str, std::map<std::string, Channel> &channel)
{
    std::map<std::string , Channel > ::iterator it = channel.find(str);
    std::map<int, e_privilege>::const_iterator const_it = it->second.getClients().find(client.getFd());

    if (const_it == it->second.getClients().end())
    {
        send_message(ERR_NOTONCHANNEL(CLIENT(client.getNick(), client.getUser()), str), client.getFd());
        return (1);
    }
    if (const_it->second != ADMIN)
    {
        send_message(ERR_CHANOPRIVSNEEDED(CLIENT(client.getNick(), client.getUser()), str), client.getFd());
        return (1);
    }
    return (0);
}

int is_already_in_channel(Client& client, std::map<std::string, Channel>::iterator it, int ClientFd, std::string nickname, std::string channel_name)
{
    std::map<int, e_privilege>::const_iterator const_it = it->second.getClients().find(ClientFd);

    if (const_it != it->second.getClients().end() && const_it->second != INVITED)
    {
        send_message(ERR_USERONCHANNEL(nickname, channel_name), client.getFd());
        return(1);
    }
    return(0);
}

void Command::inviteCommand()
{
    if(this->params.size() != 2)
    {
        send_message(ERR_NEEDMOREPARAMS(CLIENT(client.getNick(), client.getUser()), "INVITE"), this->client.getFd());
        return ;
    }

    if (not_a_user(params[0]))
        return ;

    if (not_a_channel(params[1]))
        return ;

    if (not_in_or_admin_channel(this->client, params[1], this->server.getChannels()))
        return ;

    if(is_already_in_channel(this->client, this->server.getChannels().find(params[1]), this->server.findClientFd(params[0]), params[0], params[1]))
        return ;

    this->server.getChannels().find(params[1])->second.getClients().insert(std::pair<int, e_privilege>(this->server.findClientFd(params[0]), INVITED));

    send_message(RPL_INVITESNDR(CLIENT(client.getNick(), client.getUser()), params[0], params[1]), this->client.getFd());
	send_message(RPL_INVITERCVR(CLIENT(client.getNick(), client.getUser()), params[0], params[1]), this->server.findClientFd(params[0]));
}