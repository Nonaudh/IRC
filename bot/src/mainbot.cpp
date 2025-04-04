#include "../inc/Bot.hpp"

bool Bot::Signal = false;

void	Bot::signalHandler(int sig)
{
	(void)sig;

	std::cout << std::endl;
	Bot::Signal = true;
}

int main(int argc, char **argv)
{
    std::cout <<"ALLLors"<< std::endl;

	if ((argc != 3))
	{
		std::cout << "Usage ./bot <port> <password>" << std::endl;
		return (0);
	}

	Bot B;

	try
	{
		signal(SIGINT, Bot::signalHandler);
		signal(SIGQUIT, Bot::signalHandler);
		B.MBot(argv);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	// B.closeAllFd();
	return (0);
}