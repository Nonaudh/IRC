#ifndef BOT_HPP
# define BOT_HPP

# include <sys/types.h>
# include <sys/socket.h>
# include <iostream>
# include <string>
# include <unistd.h>
# include <errno.h>
# include <stdio.h>
# include <netinet/in.h>
# include <string.h>
# include <vector>
# include <poll.h>
# include <fcntl.h>
# include <csignal>
# include <arpa/inet.h>
# include <exception>
# include <cstdlib>
# include <arpa/inet.h>
# include <sstream>

class	Bot
{
	private :
		int	port;
		std::string	password;
		int	SocketFd;
		static bool Signal;
		bool	connected;
		pollfd	pollFd;
		std::string	nickname;

	public :
		Bot(void);
		~Bot(void);
		int getFd();
		void		MBot(char **argv);
		static void	signalHandler(int sig);
		int			initializeBot(char **argv);
		void		connectToServ(void);
		void		authentificateToServ(void);
		void		handleServerResponse(std::string buff);
		void		check_connection(std::string buff);
		void		bot_response(std::string buff);
		void		runBot(void);

};

# endif