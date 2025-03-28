#ifndef CLIENT_HPP
# define CLIENT_HPP

#include <string>

enum	e_level
{
	NONE,
	PASSWORD,
	CONNECT,
	OP,
};

class	Client
{
	private :
		e_level		level;
		std::string	username;
		std::string	nickname;
		int			SocketFd;

	public :
		Client(int socketFd);

	Client();

	~Client(void);
		void	setFd(int fd);
		int		getFd(void) const;
		void	Authen(e_level level);
		e_level		getAuthen(void) const;
		std::string	getNick(void) const;
		void		setNick(std::string str);
		std::string	getUser(void) const;
		void		setUser(std::string str);
};

# endif