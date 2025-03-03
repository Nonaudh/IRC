#include "irc.hpp"

Server::Server(void)
{
	this->serSocketFd = -1;
	this->Signal = false;
}

Server::~Server(void)
{}

typedef struct s_command
{
	int socketFd;
	std::string command;
	std::vector<std::string> params;
} t_command;

std::vector<std::string> split(char * str, char sep) {
	std::vector<std::string> ret;

	(void) sep;

	char e[2] = " ";
	char *token = strtok(str, e);

	while (token)
	{
		std::cout << token << std::endl;
		token = strtok(str, e);
	}

	return ret;
}

void	Server::handleData(int socketFd)
{
	char	buff[1024];
	bzero(buff, sizeof(buff));
	t_command command = {};

	ssize_t bytes = recv(socketFd, buff, sizeof(buff) - 1, 0);
	if (bytes <= 0)
	{
		std::cout << "Client " << socketFd << " disconnected\n";
		close(socketFd);
		erasePoll(socketFd);
	}
	else
	{
		buff[bytes] = 0;
		command.socketFd = socketFd;
//		/*std::vector<std::string> params = */split(buff, ' ');
		std::cout << socketFd << " : " << buff;
	}
}

int	Server::enterPassword(int socketFd) // dont work because blocking the serv
{
	if (send(socketFd, "Enter password : ", 18, 0) == -1)
	{
		std::cerr << "Error : send()" << std::endl;
	}

	std::vector<pollfd>::iterator	it;

	for (it = pollfds.begin(); it < pollfds.end() && it->fd != socketFd; ++it)
		;
	poll(&*it, 1, -1);

	char	buff[1024];
	bzero(buff, sizeof(buff));

	ssize_t bytes = recv(socketFd, buff, sizeof(buff) - 1, 0);
	if (bytes <= 0)
	{
		std::cout << "Client " << socketFd << " disconnected\n";
		close(socketFd);
		erasePoll(socketFd);
		return (1);
	}
	else
	{
		buff[bytes - 1] = 0;
		if (buff != password)
		{
			send(socketFd, "Wong password sorry\n", 21, 0);
			close(socketFd);
			erasePoll(socketFd);
			return (1);
		}
	}
	return (0);
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
	// if (enterPassword(socketFd))
	// 	return ;
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
