#include "irc.hpp"

#include <cstring>
#include <iostream>
#include <iterator>
#include <map>
#include "Command.hpp"
#include <algorithm>


bool Server::Signal = false;

Server::Server(void)
{
	this->serSocketFd = -1;
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

void execCmd(Server& server, Client& client, char *buff) {
	std::vector<std::string> splitted;
	std::string command_name;

	splitted = split(buff, " ");

	if (splitted.empty())
		return;

	command_name = splitted[0];
	splitted.erase(splitted.begin());

	Command(server, client, command_name, splitted).execute();
}

int	skipped_b_s(char c)
{
	return (c == '\n' || c == '\r');
}

int	unskipped_b_s(char c)
{
	return (!(c == '\n' || c == '\r'));
}

int	skipped_space(char c)
{
	return (c == ' ' || c == '	');
}

int	unskipped_space(char c)
{
	return (!(c == ' ' || c == '	'));
}

void	new_execCmd(Server& server, Client& cli, std::vector<std::string> v)
{
	std::vector<std::string> splitted;
	std::string command_name;

	for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); ++it)
	{
		splitted = ft_split_irc(*it, skipped_space, unskipped_space);
		command_name = *splitted.begin();
		splitted.erase(splitted.begin());
		Command(server, cli, command_name, splitted).execute();
		splitted.clear();
		command_name.clear();
	}
}

std::vector<std::string> ft_split_irc(std::string buff, int (*skip)(char), int (*unskip)(char))
{
	std::vector<std::string>	v;
	
	std::string::iterator first = buff.begin();
	std::string::iterator last;

	while (first != buff.end())
	{
		first = std::find_if(first, buff.end(), unskip);
		last = std::find_if(first, buff.end(), skip);

		std::string tmp(first, last);

		if (first != last)
			v.push_back(tmp);
		tmp.erase();
		first = last;
	}
	return (v);
}

void	print_vector(std::vector<std::string>& v)
{
	for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); ++it)
		std::cout << *it << " | " << std::endl;
}

bool	no_endl(std::string	buff)
{
	
	if (std::find(buff.begin(), buff.end(), '\n') == buff.end())
		return (1);
	return (0);
}

void	Server::readData(Client& cli)
{
	char	bufftmp[1024];
	std::string	buff;
	static std::map<int, std::string> save;
	bzero(bufftmp, sizeof(bufftmp));

	ssize_t bytes = recv(cli.getFd(), bufftmp, sizeof(bufftmp) - 1, 0);
	if (bytes <= 0)
	{
		std::cout << "Client " << cli.getFd() << " disconnected\n";
		close(cli.getFd());
		erasePoll(cli.getFd());
		eraseClient(cli.getFd());
	}
	else
	{
		bufftmp[bytes] = 0;
		buff = bufftmp;
		std::map<int, std::string>::iterator it;
		it = save.find(cli.getFd());
		if (it != save.end())
		{
			buff = save.find(cli.getFd())->second + buff;
			save.erase(it);
		}
		if (no_endl(buff))
		{
			save.insert(std::pair<int,std::string>(cli.getFd(), buff));
			return ;
		}
		std::vector<std::string> v = ft_split_irc(buff, skipped_b_s, unskipped_b_s);
		print_vector(v);
		// execCmd(*this, cli, buff);
		new_execCmd(*this, cli, v);
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
	while (Server::Signal == false)
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
