#ifndef SERVER_HPP
# define SERVER_HPP

# include <vector>
#include "Command.hpp"

class	Server
{
	private :
		int	port;
		std::string password;
		int	serSocketFd;
		bool Signal;
		std::vector<struct pollfd> pollfds;

	public :
		Server(void);
		~Server(void);

		void	irc(char **argv);
		int		setPortPassword(char **argv);
		int		enterPassword(int socketFd);
		void	createServer(void);
		void	runServer(void);
		void	NewClient(void);
		void	handleData(int socketFd);
		void	addToPoll(int socketFd);
		void	erasePoll(int socketFd);
		Command parseCommand(int socketFd, char *buff);
};

#endif