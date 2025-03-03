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
		Client(void);
		~Client(void);
		void	authenticate(void);

};

# endif