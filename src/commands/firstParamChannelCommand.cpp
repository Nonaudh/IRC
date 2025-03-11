#include "Command.hpp"

std::map<std::string, Channel>::iterator  verifChanneExisted(std::map<std::string, Channel>& channels, std::vector<std::string> params)
{
    params[0].erase (params[0].begin());
    std ::cout << "0 = "<< params[0] << std::endl;
    std::map <std::string, Channel> :: iterator it = channels.find(params[0]);
    return(it);
}
    
bool verifClientConnectServer(std::map<std::string, Channel>& channels, std::vector<std::string> params, int clientFd ,std::map<int, e_privilege> channel, int i)
{
    (void)params;
    (void)channels;
    std::map<int, e_privilege>::iterator    it = channel.find(clientFd);
    if (it != channel.end())
    {
        if(i == 0)
            std::cout << "Sur la Commande PART le clients n'est pas connecter au channel " << std::endl;
        if(i == 1)
            std::cout << "Sur la Commande TOPIC le clients n'est pas connecter au channel " << std::endl;
        if(i == 2)
            std::cout << "Sur la Commande KICK le clients n'est pas connecter au channel " << std::endl;
        if(i == 3)
            std::cout << "Sur la Commande Mode le clients n'est pas connecter au channel " << std::endl;
        return (1);
    }
    if (it->second != INVITE)//Faire des droits personnaliser pour chaque commande
    {
        if(i == 0)
            std::cout << "Sur la Commande PART le clients n'a pas les droits " << std::endl;
        if(i == 1)
            std::cout << "Sur la Commande TOPIC le clients n'a pas les droits " << std::endl;
        if(i == 2)
            std::cout << "Sur la Commande KICK le clients n'a pas les droits " << std::endl;
        if(i == 3)
            std::cout << "Sur la Commande Mode le clients n'a pas les droits " << std::endl;
        return (1);
    }
    return (0);
}

void Command::firstParamChannelCommand(int i)
{
    (void)i;
    std::cout << "Path with Partcommand" << std::endl;
   if(getParams()[0][0]== '#')
   {
       if(verifChanneExisted(this->server.getChannels(), this->getParams()) != this->server.getChannels().end())
       {
           std::cout<< "Channel existed" << std::endl;
           if(verifClientConnectServer(this->server.getChannels(), this->getParams(), this->client.getFd(),
           verifChanneExisted(this->server.getChannels(), this->getParams())->second.getClients(), i))
           {
                if(i == 0)
                    std::cout << "Execute PartCommand" << std ::endl;
                if(i == 1)
                    std::cout << "Execute TopicCommand" << std::endl;
                if(i == 2)
                    std::cout << "Execute KickCommand" << std::endl;
                if(i == 3)
                    std::cout << "Execute MODECommand" << std::endl;
            }
            return;
        }
        if(i == 0)
            std::cout << "Sur la Commande PART le channel n'existe pas" << std::endl;
        if(i == 1)
            std::cout << "Sur la Commande TOPIC le channel n'existe pas" << std::endl;
        if(i == 2)
            std::cout << "Sur la Commande KICK le channel n'existe pas" << std::endl;
        if(i == 3)
            std::cout << "Sur la Commande Mode le channel n'existe pas" << std::endl;
        std::cout << "Le channel n'existe pas" << std::endl;
        return;
    }
    //Il n'y a pas #
    if(i == 0)
    std::cout << "Sur la Commande PART il manque le #" << std::endl;
    if(i == 1)
        std::cout << "Sur la Commande TOPIC il manque le #" << std::endl;
    if(i == 2)
        std::cout << "Sur la Commande KICK il manque le #" << std::endl;
    if(i == 3)
        std::cout << "Sur la Commande Mode il manque le #" << std::endl;
    
std::cout << "Le channel n'existe pas" << std::endl;
}