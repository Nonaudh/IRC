#include "Server.hpp"
#include <iostream>
#include <exception>
#include <csignal>

int	main(int argc, char **argv)
{
	if ((argc != 3))
	{
		std::cout << "Usage ./ircserv <port> <password>" << std::endl;
		return (0);
	}

	Server S;

	try
	{
		signal(SIGINT, Server::signalHandler);
		signal(SIGQUIT, Server::signalHandler);
		S.irc(argv);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	S.closeAllFd();
	return (0);
}
