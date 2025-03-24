#include "Command.hpp"

///a ENLEVERS
//Personnalisation pour ce genre de commande MODE #channel +o <nickname> 

void printChannels(const std::map<std::string, Channel>& channels)
{
    if (channels.empty()) {
        std::cout << "Aucun channel enregistré." << std::endl;
        return;
    }

    std::cout << "Liste des channels : " << std::endl;
    for (std::map<std::string, Channel>::const_iterator it = channels.begin(); it != channels.end(); ++it)
    {
        std::cout << "=" << it->first << std::endl;
    }
    // printChannels(channels); 
}

std::map<std::string, Channel>::iterator  verifChanneExisted(std::map<std::string, Channel>& channels, std::vector<std::string> params)
{
    //params[0].erase (params[0].begin());//Je ne sais pas pourquoi mets # rester
    std::map <std::string, Channel> :: iterator it = channels.find(params[0]);
    return(it);
}
    
