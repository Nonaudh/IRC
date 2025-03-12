#ifndef SERVER_HPP
# define SERVER_HPP

# include <vector>
# include "Client.hpp"
#include "Channel.hpp"
#include <map>
#include <sys/poll.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>

class	Server
{
	private :
		int	port;
		std::string password;
		int	serSocketFd;
		static bool Signal;
		std::vector<pollfd> pollfds;
		std::vector<Client>	clients;
		std::map<std::string, Channel > channels;

	public :
		Server(void);
		~Server(void);

		void	irc(char **argv);

		bool	checkPassword(std::string const& password);
		static void	signalHandler(int sig);
		void	closeAllFd(void);
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
		//Modifier pour la class channel
		void createChannel(std::string const& name, int fd);
		Channel* findChannel(std::string const& findChannel);
		void 	joinChannel(std::string const & nameChannel, int fd);
		std::map<std::string, Channel>&	getChannels(void);
		std::vector<Client>&	getClient(void);
		void	killFromServer(std::string nickname, std::string reason);
};

void	send_message(const char *str, int fd);

std::vector<std::string> split(std::string buff, int (*skip)(char), int (*unskip)(char));

#endif