#ifndef SERVER_HPP
# define SERVER_HPP

# include <vector>

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

		void	irc(void);
		void	createServer(void);
		void	runServer(void);
		void	NewClient(void);
		void	handleData(int& fd);
};

#endif