#ifndef CLIENT_HPP
# define CLIENT_HPP

#include <string>

enum	e_level
{
	AUTHEN,
	CONNECT,
	OP,
};

class	Client
{
	private :
		e_level		authentication;
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
};

# endif