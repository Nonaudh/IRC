#include "irc.hpp"

#include <cstring>
#include <iostream>
#include <iterator>
#include <map>
#include <algorithm>
#include "Command.hpp"
#include "Server.hpp"


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

std::vector<std::string> split(char *str, const char *sep) {
	std::vector<std::string> ret;

	if (!str || !sep) return ret;

	char *token = strtok(str, sep);

	while (token != NULL) {
		ret.push_back(std::string(token));
		token = strtok(NULL, sep);
	}

	return ret;
}

void execCmd(Server server, Client& client, char *buff) {
	std::vector<std::string> splitted;
	std::string command_name;

	splitted = split(buff, " ");

	if (splitted.empty())
		return;

	std::string &last = splitted.back();

	if (!last.empty() && (last[last.size() - 1] == '\n' || last[last.size() - 1] == '\r')) {
		last.erase(last.size() - 1);
	}

	std::transform(splitted[0].begin(), splitted[0].end(), splitted[0].begin(), ::toupper);
	command_name = splitted[0];
	splitted.erase(splitted.begin());

	Command(server, client, command_name, splitted).execute();
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
		execCmd(*this, cli, buff);
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

bool Server::checkPassword(const std::string &password) {
	std::cout << "Checking password: " << password << " size: " << password.size() << std::endl;
	std::cout << "Server password: " << this->password << " size: " << this->password.size() << std::endl;

	for (size_t i = 0; i < password.size(); i++) {
		std::cout << (int)password[i] << " ";
	}

	std::cout << std::endl;

	return password == this->password;
}
