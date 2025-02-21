#include "irc.hpp"

int	main(int argc, char **argv)
{
	Server S;

	try
	{
		S.irc();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}