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
	// authentication = false;
	authentication = CONNECT; // to switch to false
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
	this->authentication = level;
}

e_level		Client::getAuthen(void) const
{
	return (this->authentication);
}

std::string	Client::getNick(void) const
{
	return (this->nickname);
}

void		Client::setNick(std::string str)
{
	this->nickname = str;
}
