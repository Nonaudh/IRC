# include "Client.hpp"

Client::Client(void)
{
	authentication = false;
	SocketFd = -1;
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
