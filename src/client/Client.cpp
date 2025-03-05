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
	authentication = false;
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

void	Client::Authen(void)
{
	this->authentication = true;
}

int		Client::getAuthen(void) const
{
	return (this->authentication);
}
