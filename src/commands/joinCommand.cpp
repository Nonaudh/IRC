#include "Command.hpp"

//MIse au propre de la command
#include <iterator>  // Pour std::distance

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

int	searchNbrChannels(std::vector<std::string>& params)
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

std::vector<std::string> ::const_iterator searchMdp(int i, std::string search, std::vector <std::string> params)//Je ne suis pas sur de celle mais cpp
{
	std::vector<std::string> :: const_iterator const_it = std::find(params.begin(), params.end(), search);
	for(int t = 0; t != i; ++t)
		const_it++;
	return(const_it);
}

void Command::joinCommand()
{
	//Ce qui permet d'obternir l'adresse du channel
	std::map<std::string, Channel>& channels = this->getServer().getChannels();

	//Ce qui permet d'obtenir l'iterateur sur le vecteur
	std::vector <std::string> params = getParams();

	//Ce qui permet de determiner le nbr de mots de pass
	int searchNbrChannel= searchNbrChannels(this->params);

	//Ce qui permet determiner le nombre de channell
	int  searchMdpChannel =getParams().size()- searchNbrChannel;

	std::vector <std::string> ::const_iterator const_it;
	//Creation d'une boucle permettant de vois si le canal existe
	for( const_it= params.begin(); const_it != params.end() - searchMdpChannel;++const_it)
	{
		//Creation d'une copie de l'iterateur
		std::vector <std::string>::const_iterator copie = const_it;
		std::map<std::string,Channel>::iterator it = channels.find(*const_it);
		if (it == channels.end())
		{
			if (std::distance(static_cast<std::vector<std::string>::const_iterator>(params.begin()), const_it)+ searchNbrChannel < (int)params.size()&& searchMdpChannel != 0)
				channels.insert(std::pair<std::string, Channel>(*const_it, Channel(client.getFd(), *const_it,  *(searchMdp((searchNbrChannel), *copie, params)))));
			else//Creation du canal sans mdp
				channels.insert(std::pair<std::string, Channel>(*const_it, Channel(client.getFd(), *const_it, "")));
			send_message(RPL_JOIN(CLIENT(client.getNick(), client.getUser()), *const_it), client.getFd());
		} 
		 else
		 {
		 	// Le canal existe, vous pouvez le rejoindre
			if (std::distance(static_cast<std::vector<std::string>::const_iterator>(params.begin()), const_it)+ searchNbrChannel < (int)params.size()&& searchMdpChannel != 0)
				 it->second.joinChannel(client, USER,  *(searchMdp((searchNbrChannel - searchMdpChannel), *copie, params)), this->getServer());
		 	else //Rejoindre sans mdp
		 		it->second.joinChannel(client, USER,  "", this->getServer());
		 }
	}
}
