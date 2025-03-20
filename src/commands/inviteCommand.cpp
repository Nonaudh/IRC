#include "Command.hpp"
#include <stdio.h>


// ERR_USERONCHANNEL
// RPL_INVITING

int Command::not_a_user(std::string str)
{
    std::vector<Client>& clients = this->server.getClient();
    std::vector<Client>::iterator it;

    for (it = clients.begin(); it != clients.end() && str != it->getNick(); ++it)
        ;
    if (it == clients.end())
    {
        send_message(ERR_NOSUCHNICK(str), this->client.getFd());
        return (1);
    }
    return (0);
}

int Command::not_a_channel(std::string str)
{
    std::map<std::string, Channel>::iterator    it = this->server.getChannels().find(str);

    if (it == this->server.getChannels().end())
    {
        send_message(ERR_NOSUCHNICK(str), this->client.getFd());
        return (1);
    }
    return (0);
}

int not_in_or_admin_channel(int fd, std::string str, std::map<std::string, Channel> &channel)
{
    std::map<std::string , Channel > ::iterator it = channel.find(str);
    std::map<int, e_privilege>::const_iterator const_it = it->second.getClients().find(fd);

    if (const_it == it->second.getClients().end())
    {
        send_message(ERR_NOTONCHANNEL(str), fd);
        return (1);
    }
    if (const_it->second != ADMIN)
    {
        send_message(ERR_CHANOPRIVSNEEDED(str), fd);
        return (1);
    }
    return (0);
}

int is_already_in_channel(int fd, std::map<std::string, Channel>::iterator it, int ClientFd, std::string nickname, std::string channel_name)
{
    std::map<int, e_privilege>::const_iterator const_it = it->second.getClients().find(ClientFd);

    if (const_it != it->second.getClients().end() && const_it->second != INVITED)
    {
        send_message(ERR_USERONCHANNEL(nickname, channel_name), fd);
        return(1);
    }
    return(0);
}

void Command::inviteCommand()
{
    if(this->params.size() != 2)
    {
        send_message(ERR_NEEDMOREPARAMS("INVITE"), this->client.getFd());
        return ;
    }

    if (not_a_user(params[0]))
        return ;

    if (not_a_channel(params[1]))
        return ;

    if (not_in_or_admin_channel(this->client.getFd(), params[1], this->server.getChannels()))
        return ;

    if(is_already_in_channel(this->client.getFd(), this->server.getChannels().find(params[1]), this->server.findClientFd(params[0]), params[0], params[1]))
        return ;

    this->server.getChannels().find(params[1])->second.getClients().insert(std::pair<int, e_privilege>(this->server.findClientFd(params[0]), INVITED));

    send_message(RPL_INVITING(params[1], params[0]), this->client.getFd());
}
