#include "../inc/Bot.hpp"

bool Bot::Signal = false;

std::string	int_to_string(int nb)
{
	std::ostringstream	str;

	str << nb;

	return (str.str());
}

Bot::Bot(void)
{}

Bot::~Bot(void)
{}

int	Bot::initializeBot(char **argv)
{
	port = atoi(argv[1]);
	//check port range
	password = argv[2];
	return (0);
}

void	Bot::connectToServ(void)
{
	sockaddr_in	add;

	add.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &add.sin_addr.s_addr);
	add.sin_port = htons(this->port);

	this->SocketFd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->SocketFd == -1)
		throw(std::runtime_error("Error : socket()"));

	if (connect(this->SocketFd, (sockaddr *)&add, sizeof(add)) == -1)
		throw(std::runtime_error("Error : connect()"));
}

void		Bot::authentificateToServ(void)
{
	std::string msg = "PASS " + this->password + "\r\n";
	send(this->SocketFd, msg.c_str(), msg.length(), 0);

	msg = "NICK BOT_" + int_to_string(this->SocketFd) + "\r\n";
	send(this->SocketFd, msg.c_str(), msg.length(), 0);

	msg = "USER BOT 0 * :realname\r\n";
	send(this->SocketFd, msg.c_str(), msg.length(), 0);
}

void	Bot::handleServerResponse(void)
{
	;
}

void	Bot::runBot(void)
{
	while (Bot::Signal == false)
	{
		;
	}
}

void	Bot::MBot(char **argv)
{
	initializeBot(argv);
	connectToServ();
	authentificateToServ();
	handleServerResponse();
	runBot();
}
