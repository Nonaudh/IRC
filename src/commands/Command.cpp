#include "Command.hpp"
# include "Server.hpp"

#include <sys/socket.h>

Command::Command(Server &server, Client &client, std::string command, std::vector <std::string> params)
	: server(server), client(client), command(command), params(params) {
}

Command::~Command() {

}

Server& Command::getServer() {
	return server;
}

Client& Command::getClient() {
	return client;
}

std::string Command::getName() {
	return this->command;
}

std::vector <std::string> Command::getParams() {
	return this->params;
}

void Command::joinCommand()
{
	std::map<std::string, Channel>& channels = this->getServer().getChannels();
	std::cout << "SocketFd: " << getClient().getFd() << std::endl;
	std::cout << "Command: " << getName() << std::endl;
	std::cout << "Args: ";
	for (unsigned long i = 0; i < getParams().size(); ++i) {
		std::cout << getParams()[i];
	}
	std::cout << "Avant ajout : " << channels.size() << " canaux" << std::endl;

	// Chercher si le canal existe déjà
	std::map<std::string, Channel>::iterator it = channels.find(getParams()[0]);

	if (it == channels.end()) {
		// Le canal n'existe pas, créez-le
		std::cout << "Canal créé : " << "command" << std::endl;
		channels.insert(std::pair<std::string, Channel>(getParams()[0], Channel(client.getFd(), getParams()[0])));
		std::cout << "Apres insert : " << channels.size() << " canaux" << std::endl;
	} else {
		std::cout << "Canal existant : " << "command" << std::endl;
		// Le canal existe, vous pouvez le rejoindre
		it->second.joinChannel(client.getFd(), USER);
	}

	// Affichage des informations
	std::cout << "SocketFd: " << getClient().getFd() << std::endl;
	std::cout << "Command: " << getName() << std::endl;
	std::cout << "Args: ";
	for (unsigned long i = 0; i < getParams().size(); ++i) {
		std::cout << getParams()[i];
	}
	std::cout << std::endl;
}

void	Command::killCommand(void)
{
	switch (this->params.size())
	{
		case 0:
			send_message("Error killCommand\r\n", this->client.getFd());
			break;
		
		case 1:
			this->server.killFromServer(params[0], "");
			break;
		
		default:
			this->server.killFromServer(params[0], params[1]);
	}
}

void Command::execute() {
	if (!client.getAuthen()) {
		if (this->command == "PASS")
			this->passCommand();
		return;
	}

	std::string	cmd_available[] = {"KILL", "QUIT", "JOIN", "NICK", "PRIVMSG"};

	int	i;
	for (i = 0; !cmd_available[i].empty() && command != cmd_available[i]; ++i)
		;

	switch (i)
	{
		case (KILL):
			killCommand();
			break ;
		case (QUIT):
			quitCommand();
			break ;
		case (JOIN):
			joinCommand();
			break ;
		case (NICK) :
			nickCommand();
			break ;
		case (PRIVMSG):
		{
			std::cout << ("XXX") << std::endl;
			privmsgCommand();
		}
			break ;

		default:
			std::cout << "Unknow cmd : " << command << std::endl;
			break ;
	}
}//PRIVMSG #channelname :Hello, everyone! 

void Command::quitCommand() {
	std::cout << "QuitCommand" << std::endl;

	std::cout << "SocketFd: " << getClient().getFd() << std::endl;
	std::cout << "Command: " << getName() << std::endl;
	std::cout << "Args: ";
	for (unsigned long i = 0; i < getParams().size(); ++i) {
		std::cout << getParams()[i];
	}

	std::cout << std::endl;
}

void Command::passCommand() {
	std::cout << "PassCommand" << std::endl;

	std::cout << "SocketFd: " << getClient().getFd() << std::endl;
	std::cout << "Command: " << getName() << std::endl;
	std::cout << "Args: ";
	for (unsigned long i = 0; i < getParams().size(); ++i) {
		std::cout << getParams()[i];
	}
	std::cout << std::endl;

	int socketFd = client.getFd();

	if (params.size() != 1) {
		send(socketFd, "Usage: PASS <password>\n", 23, 0);
		return;
	}

	if (!getServer().checkPassword(params[0])) {
		send(socketFd, "Wrong password, try again\n", 26, 0);
		return;
	}

	client.Authen(CONNECT);

	send(socketFd, "You're now connected\n", 22, 0);
	std::cout << socketFd << " is now connected to the server" << std::endl;
}
