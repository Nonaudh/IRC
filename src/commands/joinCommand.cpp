#include "Command.hpp"

//MIse au propre de la command
#include <stdio.h>

int searchMdpJoin(std::vector<std::string> Params, size_t j, int i)
{
	int countMdp = 0;
	int countChannel=0;
	for(size_t i = 0; i != j; ++i)
	{
		if(Params[i][0] != '#' && Params[i][0] != '&')
			countMdp++;
		else
			countChannel++;
	}
	if(i == 0)
		return(countMdp);
	else 
		return(countChannel);
}

int	searchMdpJoincplus(std::vector<std::string>& params)
{
	int	countMdp = 0;
	std::string	c = "#&";

	for (std::vector<std::string>::iterator it = params.begin(); it != params.end(); ++it)
	{
		if (c.find(*it->begin()) != std::string::npos)
			countMdp++;
	}
	return (countMdp);
}

void Command::joinCommand()
{
	//Ce qui permet d'obternir l'adresse du channel
	std::map<std::string, Channel>& channels = this->getServer().getChannels();

	//Ce qui permet de determiner le nbr de mots de pass
	int searchMdpChannel = searchMdpJoincplus(this->params);
	std::cout << "nb of mdp : " << searchMdpChannel << std::endl;

	//Ce qui permet determiner le nombre de channell
	int searchNbrChannel = searchMdpJoin(getParams(), getParams().size(), 1) ;

	//Creation d'une boucle permettant de vois si le canal existe
	for(unsigned long i = 0; i != getParams().size()-searchMdpChannel ; ++i)
	{
		std::map<std::string, Channel>::iterator it = channels.find(getParams()[i]);
		if (it == channels.end()) {

			// Le canal n'existe pas, créez-le
			if((getParams().size() > i + searchMdpChannel && searchMdpChannel != 0) && (getParams().size() > i + searchNbrChannel) )//Creation du canal avec mdp
				channels.insert(std::pair<std::string, Channel>(getParams()[i], Channel(client.getFd(), getParams()[i],  getParams()[i + searchNbrChannel  ])));
			else//Creation du canal sans mdp
				channels.insert(std::pair<std::string, Channel>(getParams()[i], Channel(client.getFd(), getParams()[i], "")));
		} else {
			// Le canal existe, vous pouvez le rejoindre
			if((getParams().size() > i + searchMdpChannel && searchMdpChannel != 0) && (getParams().size() > i + searchNbrChannel))//Rejoindre avec un mdp
				it->second.joinChannel(client.getFd(), USER,  getParams()[i + searchMdpChannel ]);
			else//Rejoindre sans mdp
				it->second.joinChannel(client.getFd(), USER,  "");
		}
	}
}