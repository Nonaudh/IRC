#include "irc.hpp"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <cstring>
#include <iostream>
#include <iterator>
#include <algorithm>
#include "Channel.hpp"
#include <map>
#include <sstream>


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Server::Server(void)
{
	this->serSocketFd = -1;
	this->Signal = false;
}

Server::~Server(void)
{}

void	Server::handleBuffer(Client& cli, char *buff)
{
	std::cout << buff << "s";
	std::string input(buff);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Exemple simple pour la commande JOIN
    if (input.substr(0, 5) == "JOIN ")
    {
        std::string channelName = input.substr(5);
        
        // Supprimer les espaces et le \n
        std::string::iterator it = channelName.begin();
        while (it != channelName.end())
        {
            if (*it == '\n' || *it == '\r')
                it = channelName.erase(it);
            else
                ++it;
        }
        
        Channel* chan = findChannel(channelName);
        if (!chan)
		{
			std::cout <<"Je passe par create channel FD=" << cli.getFd()<< "\n" << std::endl;
			createChannel(channelName, cli.getFd());
		}
		else
		{
			// std::cout << "CHANNELName=" <<channelName << std::endl;
			std::cout <<"Je passe par Join channel FD= " << cli.getFd() << "\n" << std::endl;
			joinChannel(channelName, cli.getFd());
		}
			// Envoyer un message au client pour confirmer
        std::stringstream ss;
        ss << ":" << cli.getFd() << " JOIN " << channelName << "\r\n";
        std::string message = ss.str();
        send(cli.getFd(), message.c_str(), message.length(), 0);
    }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (!cli.getAuthen())
	{
		if (enterPassword(cli.getFd(), buff))
		{
			std::cout << "Je sios ;a " << std::endl;
			cli.Authen();
		}
		return ;
	}
	std::cout << "C est ici" << std::endl; 
}

void	Server::handleData(Client& cli)
{
	char	buff[1024];
	bzero(buff, sizeof(buff));

	ssize_t bytes = recv(cli.getFd(), buff, sizeof(buff) - 1, 0);
	if (bytes <= 0)
	{
		std::cout << "Client " << cli.getFd() << " disconnected\n";
		close(cli.getFd());
		erasePoll(cli.getFd());
		eraseClient(cli.getFd());
	}
	else
	{
		buff[bytes] = 0;
		handleBuffer(cli, buff);
	}
}

void	Server::NewClient(void)
{
	sockaddr_in	cliadd;
	socklen_t	len = sizeof(cliadd);

	int	socketFd = accept(serSocketFd, (sockaddr *)&(cliadd), &len);
	if (socketFd == -1)
	{
		std::cerr << "Error : accept()" << std::endl;
		return ;
	}
	if (fcntl(socketFd, F_SETFL, O_NONBLOCK == -1))
	{
		std::cerr << "Error : fcntl()" << std::endl;
		return ;
	}
	addToPoll(socketFd);
	addToClient(socketFd);
	send (socketFd, "Please enter the password to connect to the server\n", 52, 0);
}

void	Server::runServer(void)
{
	while (this->Signal == false)
	{
		if ((poll(&pollfds[0], pollfds.size(), -1) == -1) && Signal == false)
			throw(std::runtime_error("Error poll()"));

		for (size_t i = 0; i < pollfds.size(); ++i)
		{
			if (pollfds[i].revents & POLLIN)
			{
				if (pollfds[i].fd == serSocketFd)
					NewClient();
				else
					handleData(findClient(pollfds[i].fd));
			}
		}
	}
}

void	Server::createServer(void)
{
	int	en = 1;
	sockaddr_in	add;

	add.sin_family = AF_INET;
	add.sin_addr.s_addr = INADDR_ANY;
	add.sin_port = htons(this->port);

	this->serSocketFd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->serSocketFd == -1)
		throw(std::runtime_error("Error : socket()"));

	if (setsockopt(this->serSocketFd, SOL_SOCKET, SO_REUSEADDR, &en, sizeof(en)) == -1)
		throw(std::runtime_error("Error : setsockopt()"));

	if (fcntl(this->serSocketFd, F_SETFL, O_NONBLOCK) == -1)
		throw(std::runtime_error("Error : fcntl()"));

	if (bind(this->serSocketFd, (sockaddr *)&add, sizeof(add)) == -1)
		throw(std::runtime_error("Error : bind()"));

	if (listen(this->serSocketFd, SOMAXCONN) == -1)
		throw(std::runtime_error("Error : listen()"));
	addToPoll(serSocketFd);
}

void	Server::irc(char **argv)
{
	if (setPortPassword(argv))
	{
		std::cout << "Error arguments" << std::endl;
		return ;
	}
	createServer();
	runServer();
}

//Modifier pour la class channel
void Server::createChannel(std::string const& name, int fd)
{
	std::cout << "CLASS SERVER CREATECHANNE;" << std::endl;
	Channel name(fd, name);
	//C'est ici qu'il faut agir
	name.createChannel(0, fd);
	channels[name]= newChanne;
}

Channel* Server::findChannel(std::string const& findChannel)
{
	std::map<std::string, Channel>:: iterator it = channels.find(findChannel);
    if (it != channels.end())
        return &(it->second);
    return NULL;
}
void 	Server::joinChannel(std::string const & nameChannel, int fd)
{
	std::cout <<"WW"<< std::endl;
	Channel *chan = findChannel(nameChannel);
	if(chan)
	{
		chan->joinChannel(1,fd);
	}
	//Verifier si il faut le creer ici 
}