#include "irc.hpp"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <cstring>
#include <iostream>
#include <iterator>
#include <algorithm>
#include "Channel.hpp"
#include <map>
#include <sstream>
#include "Command.hpp"


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
	std::string	str = buff;
	std::cout << str;

	if (!cli.getAuthen())
	{
		// if (enterPassword(cli.getFd(), buff)) // to change
		// 	cli.Authen();
		return ;
	}
	std::cout << "C est ici" << std::endl; 
}

int	Server::enterPassword(int socketFd, char *buff)
{
	if (buff != password + "\n")
	{
		if (buff != password)
		{
			send(socketFd, "Wrong password, try again\n", 26, 0);
			send(socketFd, "Wrong password, try again\n", 27, 0);
			return (0);
		}
		else
		{
			send(socketFd, "You're now connected\n", 22, 0);
			std::cout << socketFd << " is now connected to the server" << std::endl;
		}
	}

	return (1);
}

std::vector<std::string> split(char *str, const char *sep) {
	std::vector<std::string> ret;

	if (!str || !sep) return ret;

	char *token = strtok(str, sep);

	size_t len = strlen(str);
	if (len > 0 && str[len - 1] == '\n') {
		str[len - 1] = '\0';
	}

	while (token != NULL) {
		ret.push_back(std::string(token));
		token = strtok(NULL, sep);
	}

	return ret;
}

Command parseCommand(Server server, Client client, char *buff) {
	Command command;
	std::vector<std::string> splitted;
	std::string command_name;

	splitted = split(buff, " ");

	if (splitted.empty())
		return command;

	command_name = splitted[0];
	splitted.erase(splitted.begin());

	return Command(server, client, command_name, splitted);
}

void	Server::readData(Client& cli)
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

//		std::cout << "Client " << cli.getFd() << " send : " << buff << std::endl;
		Command command = parseCommand(*this, cli, buff);

/*		if (!cli.getAuthen())
		{
			if (command.getName() != "PASS")
				return;

		}*/

		command.execute();
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
					readData(findClient(pollfds[i].fd));
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
	Channel newChanne(fd, name);
	//C'est ici qu'il faut agir
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