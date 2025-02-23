#include "irc.hpp"

Server::Server(void)
{
	this->serSocketFd = -1;
	this->Signal = false;
}

Server::~Server(void)
{}

void	Server::handleData(int& fd)
{
	char	buff[1024];
	bzero(buff, sizeof(buff));

	ssize_t bytes = recv(fd, buff, sizeof(buff) - 1, 0);
	if (bytes <= 0)
	{
		std::cout << "Client disconected\n";
		close(fd);
		fd = -1;
	}
	else
	{
		buff[bytes] = 0;
		std::cout << "Data : " << buff;
	}
}

void	Server::NewClient(void)
{
	struct sockaddr_in	cliadd;
	struct pollfd		newPoll;
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

	newPoll.fd = socketFd;
	newPoll.events = POLLIN;
	newPoll.revents = 0;

	pollfds.push_back(newPoll);

	std::cout << "New client connected\n";
}

void	Server::runServer(void)
{
	while (this->Signal == false)
	{
		if ((poll(&pollfds[0], pollfds.size(), -1) == -1))
			throw(std::runtime_error("Error poll()"));

		for (size_t i = 0; i < pollfds.size(); ++i)
		{
			if (pollfds[i].revents & POLLIN)
			{
				if (pollfds[i].fd == serSocketFd)
					NewClient();
				else
					handleData(pollfds[i].fd);
			}
		}
	}
}

void	Server::createServer(void)
{
	int	en = 1;
	struct sockaddr_in	add;
	struct pollfd	NewPoll;

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

	if (bind(this->serSocketFd, (struct sockaddr *)&add, sizeof(add)) == -1)
		throw(std::runtime_error("Error : bind()"));

	if (listen(this->serSocketFd, SOMAXCONN) == -1)
		throw(std::runtime_error("Error : listen()"));

	NewPoll.fd = serSocketFd;
	NewPoll.events = POLLIN;
	NewPoll.revents = 0;
	this->pollfds.push_back(NewPoll);
}

void	Server::irc(void)
{
	this->port = 6667;

	createServer();
	runServer();

}