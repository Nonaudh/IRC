#include "Command.hpp"
#include "executeCommand.cpp"

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
    
bool verifClientConnectServer(std::map<std::string, Channel>& channels, std::vector<std::string> params, int clientFd ,std::map<int, e_privilege> channel, int i)
{
    //iL FAUT VERIFIER LES RETOUR DES CONDTITIONS
    (void)params;
    (void)channels;
    std::map<int, e_privilege>::iterator    it = channel.find(clientFd);
    std::cout << "qqq " << std::endl;

    if (it == channel.end())
    {
        if(i == 0)
            std::cout << "Sur la Commande PART le clients n'est pas connecter au channel " << std::endl;
        if(i == 1)
            std::cout << "Sur la Commande TOPIC le clients n'est pas connecter au channel " << std::endl;
        if(i == 2)
            std::cout << "Sur la Commande KICK le clients n'est pas connecter au channel " << std::endl;
        if(i == 3)
            std::cout << "Sur la Commande Mode le clients n'est pas connecter au channel " << std::endl;
        return (0);
    }
    if (it->second == INVITE)//Faire des droits personnaliser pour chaque commande
    {
        if(i == 0)
            std::cout << "Sur la Commande PART le clients n'a pas les droits " << std::endl;
        if(i == 1)
            std::cout << "Sur la Commande TOPIC le clients n'a pas les droits " << std::endl;
        if(i == 2)
            std::cout << "Sur la Commande KICK le clients n'a pas les droits " << std::endl;
        if(i == 3)
            std::cout << "Sur la Commande Mode le clients n'a pas les droits " << std::endl;
        return (0);
    }
    return (1);
}

void Command::firstParamChannelCommand(int i)
{
    std::cout << "Path with Partcommand" << std::endl;
   if(getParams()[0][0]== '#')
   {        
       if(verifChanneExisted(this->server.getChannels(), this->getParams()) != this->server.getChannels().end())
       {
           std::cout<< "Channel existed" << std::endl;
           if(verifClientConnectServer(this->server.getChannels(), this->getParams(), this->client.getFd(),
           verifChanneExisted(this->server.getChannels(), this->getParams())->second.getClients(), i))
           {
                std::cout << "CHANNEL AND CLIENTS CONNECTED " << std::endl;
                //Verifier si il manque des arguments

                if(getParams()[1].empty())
                {
                    if(i == 0)
                        std::cout << "Pour Execute PartCommand il manque arguments" << std ::endl;
                    if(i == 1)
                        std::cout << "Pour Execute TopicCommand il manque arguments" << std::endl;
                    if(i == 2)
                        std::cout << "Pour Execute KickCommand il manque arguments" << std::endl;
                    if(i == 3)
                        std::cout << "Pour Execute MODECommand il manque arguments" << std::endl;
                    return;    
                }
            //     //Mise en place de la recherche d'options
                    if (getParams().size() > 1 && !getParams()[1].empty() && (getParams()[1][0] == '-' || getParams()[1][0] == '+') && i == 3)
                    {
                    //Il n'y des options que pour mode
                          std::cout << "Mise en place des options pour Mode"<< std::endl;    
                    }
                 if(getParams().size() > 1 && !getParams()[1].empty() && (getParams()[1][0]== '-' ||getParams()[1][0]== '+' ))
                {
                    //Not with others commande'
                    if(i == 0)
                        std::cout << "Sur la Commande PART Cette commande ne prends pas d'options" << std::endl;
                    if(i == 1)
                        std::cout << "Sur la Commande TOPIC Cette commande ne prends pas d'options" << std::endl;
                    if(i == 2)
                        std::cout << "Sur la Commande KICK Cette commande ne prends pas d'options" << std::endl;
                }
                if(i == 0)
                {
                    std::cout << "Execute PartCommand" << std ::endl;
                    executePartCommand();
                }
                if(i == 1)
                    std::cout << "Execute TopicCommand" << std::endl;
                if(i == 2)
                    std::cout << "Execute KickCommand" << std::endl;
                if(i == 3)
                    std::cout << "Execute Avoir car Mode sans options peux donner des erreurs MODECommand" << std::endl;
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
// std ::cout << "\n0 = "<< params[0] << std::endl;
// std ::cout << "\n1 = "<< params[1] << std::endl;