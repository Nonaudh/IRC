#include "irc.hpp"

int	main(__attribute__((unused)) int argc, char **argv)
{
	Server S;

	(void)argv;
	try
	{
		S.irc();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}