#include "Command.hpp"

//MIse au propre de la command
#include <stdio.h>

std::vector<std::string> ft_split(size_t begin, std::string arg, int index)
{
	size_t i ;
	std::vector <std::string> chan;
	// int save = 0;
	std::string tmps;
	for( i = begin; i != arg.size(); ++i)
	{
		if(arg[i] == ',')
		{
			if(!tmps.empty())
			{
				chan.push_back(tmps);
				tmps.clear();
			}		
		}
		else
			tmps+= arg[i];
	}
	if(!tmps.empty())
	{
		chan.push_back(tmps);
		tmps.clear();
	}
	//Print pouverification
	std::vector<std::string>::iterator it;
	std::cout << "\n JE SUIS = "<< arg[index] << "\n";
	for(it = chan.begin(); it!= chan.end(); ++it )
	{
		std::cout << "Je suis la save = " << *it << std::endl;
	}
	return(chan);
}
std::vector<std::string> Command::searchAllChannel(std::vector<std::string> arg, int i)
{
	std::size_t bob = arg[i].find('#');
	std::vector <std::string> argtest;
	std::cout << "Il y a en a plusieurs je suis la place =" << bob  <<std::endl;
	if(bob !=0)
	{
		argtest=ft_split(0, arg[i], i);
	}
	return(argtest);
}

void Command::joinCommand()
{

	//Creation d'une fonction permettant de determiner si il y a ou non plusieurs channnels 

	//Ce qui permet de separer la recherche de channel;	
	std::vector<std::string> joinsearchChannel = searchAllChannel(getParams(), 0);
	//Ce qui permet de separer la recherche de mots de passe
	std::vector<std::string> joinsearchmdpChannel = searchAllChannel(getParams(), 1);
	
	(void)joinsearchmdpChannel;
	std::map<std::string, Channel>& channels = this->getServer().getChannels();
	std::cout << "SocketFd: " << getClient().getFd() << std::endl;
	std::cout << "Command: " << getName() << std::endl;
	std::cout << "Args: ";
	for (unsigned long i = 0; i < getParams().size(); ++i) {
		std::cout << getParams()[i];
	}
	std::cout << "Avant ajout : " << channels.size() << " canaux" << std::endl;

	// Chercher si le canal existe déjà
	std::map<std::string, Channel>::iterator it = channels.find(getParams()[0]);

	if (it == channels.end()) {
		// Le canal n'existe pas, créez-le
		std::cout << "Canal créé : " << "command" << std::endl;
		channels.insert(std::pair<std::string, Channel>(getParams()[0], Channel(client.getFd(), getParams()[0])));
		std::cout << "Apres insert : " << channels.size() << " canaux" << std::endl;
	} else {
		std::cout << "Canal existant : " << "command" << std::endl;
		// Le canal existe, vous pouvez le rejoindre
		it->second.joinChannel(client.getFd(), USER);
	}

	// Affichage des informations
	std::cout << "SocketFd: " << getClient().getFd() << std::endl;
	std::cout << "Command: " << getName() << std::endl;
	std::cout << "Args: ";
	for (unsigned long i = 0; i < getParams().size(); ++i) {
		std::cout << (int)i<< " = "<< getParams()[i]  << "\n";
	}
	std::cout << std::endl;
}

