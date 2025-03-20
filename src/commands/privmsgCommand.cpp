#include "Command.hpp"
#include <sys/types.h>
#include <sys/socket.h>

void sendMessageAllPeople(std::vector<std::string> params, int clientFd, std::map<int, e_privilege> clients)
{
    std::string message = params[1];

    for (std::map <int, e_privilege> ::iterator it = clients.begin();it != clients.end();++it)
    {
        if(it ->first != clientFd && it ->second != INVITED)
        {
            send(it->first, message.c_str(), message.size(), 0);
        }
    }
}

bool clientInChannel(int clientFd,std::map<int, e_privilege> channel)
{
    std::map<int, e_privilege>::iterator    it = channel.find(clientFd);
    if (it != channel.end() && it->second != INVITED)
            return (1);
    return (0);
}

void sendMessageToChannel(std::map<std::string, Channel>& channels, std::vector<std::string> params, int clientFd)
{
    params[0].erase (params[0].begin());

    std::map <std::string, Channel> :: iterator it = channels.find(params[0]);
    if(it != channels.end() && clientInChannel(clientFd,it->second.getClients()))
    {
        sendMessageAllPeople(params, clientFd, it->second.getClients());
    }//Si pas trouve mettre une protection
}

void Command::privmsgCommand()
{

    //Verifier que le channel existe

    for (unsigned long i = 0; i < getParams().size(); ++i) {
        std::cout << getParams()[i];
        // if(getParams()[i] == )//Chercher channel
	}
    if(getParams()[0][0]== '#')
        sendMessageToChannel(this->server.getChannels(), this->getParams(), this->client.getFd());
    //else le channel nn'existe pas mettre une protection

}
