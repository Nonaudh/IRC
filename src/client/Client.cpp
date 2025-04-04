#include "Client.hpp"
#include <sstream>
#include <iostream>

std::string	int_to_string(int nb)
{
	std::ostringstream	str;

	str << nb;

	return (str.str());
}

Client::Client(int socketFd)
{
	std::string	id = int_to_string(socketFd);
	// level = CONNECT;
	level = NONE;
	this->SocketFd = socketFd;
}

Client::~Client(void)
{}

int	Client::getFd(void) const
{
	return (this->SocketFd);
}

void	Client::Authen(e_level level)
{
	this->level = level;
}

e_level		Client::getAuthen(void) const
{
	return (this->level);
}

std::string	Client::getNick(void) const
{
	return (this->nickname);
}

void	Client::setNick(std::string str)
{
	this->nickname = str;
}

std::string	Client::getUser(void) const
{
	return (this->username);
}

void	Client::setUser(std::string str)
{
	this->username = str;
}
