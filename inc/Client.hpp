#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <string>
# include <iostream>

enum	e_level
{
	NONE,
	PASSWORD,
	CONNECT,
	OP,
};

class	Client
{
	protected :
		e_level		level;
		std::string	username;
		std::string	nickname;
		int			SocketFd;

	public :
		Client(int socketFd);
		virtual	~Client(void);

		int		getFd(void) const;
		void	Authen(e_level level);
		e_level		getAuthen(void) const;
		std::string	getNick(void) const;
		void		setNick(std::string str);
		std::string	getUser(void) const;
		void		setUser(std::string str);
};

std::string	int_to_string(int nb);

# endif