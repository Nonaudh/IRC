#include "Command.hpp"

int	create_socket_bot(void)
{
	int	en = 1;

	int	SocketFd = socket(AF_INET, SOCK_STREAM, 0);
	if (SocketFd == -1)
		throw(std::runtime_error("Error : socket()"));

	if (setsockopt(SocketFd, SOL_SOCKET, SO_REUSEADDR, &en, sizeof(en)) == -1)
		throw(std::runtime_error("Error : setsockopt()"));

	if (fcntl(SocketFd, F_SETFL, O_NONBLOCK) == -1)
		throw(std::runtime_error("Error : fcntl()"));
	return (SocketFd);
}

void	Command::botCommand(void)
{
	int socket_fd = create_socket_bot();

	sockaddr_in	add;

	add.sin_family = AF_INET;
	add.sin_addr.s_addr = inet_addr("127.0.0.1");
	add.sin_port = htons(this->server.getPort());

	if (connect(socket_fd, (struct sockaddr*)&add, sizeof(add)) < 0)
	{
		std::cerr << "Error : connect()" << std::endl;
		return ;
	}
	this->server.addToClient(socket_fd);
	this->server.addToPoll(socket_fd);
}
