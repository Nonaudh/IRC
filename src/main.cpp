#include "irc.hpp"

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
		S.irc(argv);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}