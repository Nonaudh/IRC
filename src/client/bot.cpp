#include "Client.hpp"

Bot::Bot(int socketFd) : Client(socketFd)
{
	std::string	id = int_to_string(socketFd);
	level = CONNECT;
	this->nickname = "BOT_" + id;
	std::cout << "Hello im the new bot : " << this->nickname << std::endl;
}

Bot::~Bot()
{}

