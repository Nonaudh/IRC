#include "Client.hpp"
#include <sstream>

std::string	int_to_string(int nb)
{
	std::ostringstream	str;

	str << nb;

	return (str.str());
}

Client::Client(int socketFd)
{
	std::string	id = int_to_string(socketFd);
	username = "Client" + id;
	nickname = username + "_";
	level = CONNECT; // to switch to AUTHEN
	SocketFd = socketFd;
}

Client::~Client(void)
{}

void	Client::setFd(int fd)
{
	this->SocketFd = fd;
}

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
