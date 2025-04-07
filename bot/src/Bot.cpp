#include "../inc/Bot.hpp"

std::string	int_to_string(int nb)
{
	std::ostringstream	str;

	str << nb;

	return (str.str());
}

Bot::Bot(void)
{
	this->connected = false;
}

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
		
	this->pollFd.fd = this->SocketFd;
	this->pollFd.events = POLLIN;
	this->pollFd.revents = 0;
	this->nickname = "Bot_Marine" + int_to_string(this->SocketFd);
}

void		Bot::authentificateToServ(void)
{
	std::string msg = "PASS " + this->password + 
	"\r\nNICK " + this->nickname + 
	"\r\nUSER BOT 0 * :realname\r\n";

	send(this->SocketFd, msg.c_str(), msg.length(), 0);
}

void	Bot::check_connection(std::string buff)
{
	if (buff.find(": 001") != std::string::npos)
	{
		this->connected = true;
		std::string msg = "JOIN #QUOIFEUR\r\n";
		send(this->SocketFd, msg.c_str(), msg.length(), 0);
	}
	return ;
}

void	Bot::bot_response(std::string buff)
{
	std::cout << "BOT : " << buff << std::endl;
}

void		Bot::handleServerResponse(std::string buff)
{
	if (this->connected == false)
		check_connection(buff);
	else
		bot_response(buff);
}

void	Bot::runBot(void)
{
	char	buff[1024] = {0};

	while (Bot::Signal == false)
	{
		bzero(buff, sizeof(buff));
		if ((poll(&pollFd, 1, -1) == -1) && Bot::Signal == false)
			throw(std::runtime_error("Error poll()"));
			
		if (pollFd.revents & POLLIN)
		{
			ssize_t bytes = recv(this->SocketFd, buff, sizeof(buff) - 1, 0);
			if (bytes <= 0)
			{
				std::cout << "Bot " << this->SocketFd << " disconnected\n";
				return ;
			}
			else
			{
				buff[bytes] = 0;
				std::cout << "Received : " << buff << std::endl;
				handleServerResponse(buff);
			}
		}
	}
}

void	Bot::MBot(char **argv)
{
	initializeBot(argv);
	connectToServ();
	authentificateToServ();
	runBot();
}
