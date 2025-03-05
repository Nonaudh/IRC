#ifndef CLIENT_HPP
# define CLIENT_HPP

#include <string>

class	Client
{
	private :
		bool		authentication;
		std::string	username;
		std::string	nickname;
		int			SocketFd;

	public :
		Client(int socketFd);

	Client();

	~Client(void);
		void	setFd(int fd);
		int		getFd(void) const;
		void	Authen(void);
		int		getAuthen(void) const;
};

# endif