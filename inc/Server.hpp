#ifndef SERVER_HPP
# define SERVER_HPP

# include <vector>
# include "Client.hpp"

class	Server
{
	private :
		int	port;
		std::string password;
		int	serSocketFd;
		bool Signal;
		std::vector<pollfd> pollfds;
		std::vector<Client>	clients;
		// std::map<std::string name, Channel chan> channels;

	public :
		Server(void);
		~Server(void);

		void	irc(char **argv);
		int		setPortPassword(char **argv);
		int		enterPassword(int socketFd, char *buff);
		void	createServer(void);
		void	runServer(void);
		void	NewClient(void);
		void	readData(Client& cli);
		void	addToPoll(int socketFd);
		void	erasePoll(int socketFd);
		Client&	findClient(int socketFd);
		void	addToClient(int socketFd);
		void	eraseClient(int socketFd);
		void	handleBuffer(Client& cli, char *buff);
};

#endif