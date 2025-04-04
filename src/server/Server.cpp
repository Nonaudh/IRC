#include "irc.hpp"

#include <cstring>
#include <iostream>
#include <iterator>
#include <map>
#include <algorithm>
#include "Command.hpp"


bool Server::Signal = false;

Server::Server(void)
{
	this->serSocketFd = -1;
}

Server::~Server(void)
{}

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
	return (c == ' ' || c == '	' || c == ',');
}

int	unskipped_space(char c)
{
	return (!(c == ' ' || c == '	' || c == ','));
}

std::vector<std::string> split_exec(std::string buff, int (*skip)(char), int (*unskip)(char))
{
	std::vector<std::string>	v;

	std::string::iterator first = buff.begin();
	std::string::iterator last;

	while (first != buff.end())
	{
		first = std::find_if(first, buff.end(), unskip);
		if (*first == ':')
			last = buff.end();
		else
			last = std::find_if(first, buff.end(), skip);

		std::string tmp(first, last);

		if (first != last)
			v.push_back(tmp);
		tmp.erase();
		first = last;
	}
	return (v);
}

void	new_execCmd(Server& server, Client& cli, std::vector<std::string> v)
{
	std::vector<std::string> splitted;
	std::string command_name;

	for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); ++it)
	{
		splitted = split_exec(*it, skipped_space, unskipped_space);
		command_name = *splitted.begin();
		std::transform(command_name.begin(), command_name.end(), command_name.begin(), ::toupper);
		splitted.erase(splitted.begin());
		if (cli.getAuthen() >= CONNECT)
			Command(server, cli, command_name, splitted).execute();
		else
			Command(server, cli, command_name, splitted).executeNotAuth();
		splitted.clear();
		command_name.clear();
	}
}

std::vector<std::string> split(std::string buff, int (*skip)(char), int (*unskip)(char))
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
		std::cout << GREEN << *it << RESET << std::endl;
}

bool	no_endl(std::string	buff)
{
	if (std::find(buff.begin(), buff.end(), '\n') == buff.end())
		return (true);
	return (false);
}

void	Server::eraseInAllChannel(Client& cli)
{
	std::map<std::string, Channel>::iterator	it;

	for (it = channels.begin(); it != channels.end(); ++it)
	{
		std::map<int, e_privilege>& chan_cli = it->second.getClients();
		if (chan_cli.find(cli.getFd()) != chan_cli.end())
		{
			send_part_rply_to_channel(it->second, cli);
			chan_cli.erase(cli.getFd());
		}
	}
}

void	Server::eraseInServer(Client& cli)
{
	eraseInAllChannel(cli);
	erasePoll(cli.getFd());
	close(cli.getFd());
	eraseClient(cli.getFd());
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
		eraseInServer(cli);
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
		std::vector<std::string> v = split(buff, skipped_b_s, unskipped_b_s);
		print_vector(v);
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
		close (socketFd);
		return ;
	}
	addToPoll(socketFd);
	addToClient(socketFd);
}

void	Server::runServer(void)
{
	while (!Server::Signal)
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
				{
					std::vector<Client>::iterator it = findClient(pollfds[i].fd);
					if (it != clients.end())
						readData(*it);
				}
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

Channel* Server::findChannel(std::string const& findChannel)
{
	std::map<std::string, Channel>:: iterator it = channels.find(findChannel);
    if (it != channels.end())
        return &(it->second);
    return NULL;
}

bool Server::checkPassword(const std::string &password) {
	return password == this->password;
}
