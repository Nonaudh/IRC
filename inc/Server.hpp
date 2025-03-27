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

#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

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
		int		findClientFd(std::string nickname);
		void	addToClient(int socketFd);
		void	eraseClient(int socketFd);
		void	eraseInServer(Client& cli);
		void	eraseInAllChannel(Client& cli);
		void	handleBuffer(Client& cli, char *buff);
		//Modifier pour la class channel
		void createChannel(std::string const& name, int fd, std::string mdp);
		Channel* findChannel(std::string const& findChannel);
		void 	joinChannel(std::string const & nameChannel, int fd);
		std::map<std::string, Channel>&	getChannels(void);
		std::vector<Client>&	getClient(void);
		void	killFromServer(std::string nickname, std::string reason, int caller);
};

void	send_message(std::string str, int fd);
void	actualise_name_reply(Channel& chan, Server& serv, Client& cli);

std::vector<std::string> split(std::string buff, int (*skip)(char), int (*unskip)(char));

#endif