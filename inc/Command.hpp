#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <vector>
#include <iostream>
#include "Client.hpp"
#include "Server.hpp"
#include <algorithm>
# include <map>
# include "error.hpp"
# include <sys/types.h>
# include <sys/socket.h>
# include <cstring>
# include <unistd.h>

enum	e_cmd
{
	PASS,
	USER_CMD,
	KILL,
	QUIT,
	JOIN,
	NICK_CMD,
	PRIVMSG_CMD,
	MODE,
	TOPIC, 
	KICK,
	INVITE,
	NOTICE_CMD,
	PART
};

class Command {
public:
	Command(Server& server, Client &client, std::string command, std::vector<std::string> params);
	virtual ~Command();

	Server& getServer();
	Client& getClient();
	std::string getName();
	std::vector<std::string> getParams();

	void execute();
	void executeNotAuth();

private:
	Server& server;
	Client& client;
	std::string command;
	std::vector<std::string> params;

	void	userCommand(void);
	void	passCommand(void);
	void	quitCommand(void);
	void	joinCommand(void);
	void	nickCommand(void);
	void	kickCommand(void);
	void	privmsgCommand(void);
	void	noticeCommand(void);
	void	killCommand(void);
	void	modeCommand(void);
	void	inviteCommand(void);
	void	topicCommand(void);
	void	botCommand(void);
	int		not_a_user(std::string str);
	int		not_a_channel(std::string str);
	void	partCommand(void);

};

void	send_part_rply_to_channel(Channel& chan, Client& cli);
void	send_message(std::string str, int fd);

#endif