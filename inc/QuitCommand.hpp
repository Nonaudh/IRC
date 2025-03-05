#ifndef QUITCOMMAND_HPP
#define QUITCOMMAND_HPP

#include "Command.hpp"

class QuitCommand : public Command {
public:
	QuitCommand();
	QuitCommand(Server server, Client client, std::string command, std::vector<std::string> params);
	QuitCommand(const QuitCommand &copy);
	QuitCommand &operator=(const QuitCommand &copy);
	~QuitCommand();

	void action();
};

#endif