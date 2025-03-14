#ifndef ERROR_HPP
# define ERROR_HPP

#define ERR_NONICKNAMEGIVEN ":No nickname given\r\n"

#define ERR_NICKNAMEINUSE(nick) (std::string(nick) + " :Nickname is already in use\r\n").c_str()

#define ERR_NOPRIVILEGES ":Permission Denied- You're not an IRC operator\r\n"

#define ERR_NOSUCHCHANNEL(channel) (std::string(channel) + " :No such channel\r\n").c_str()
                        
#define ERR_CHANOPRIVSNEEDED(channel) (std::string(channel) + " :You're not channel operator\r\n").c_str()

#define ERR_NOTONCHANNEL(channel) (std::string(channel) + " :You're not on that channel\r\n").c_str()
                       
#define ERR_NOSUCHNICK(nick) (std::string(nick) + " :No such nick/channel\r\n").c_str()

#define ERR_NEEDMOREPARAMS(cmd) (std::string(cmd) + " :Not enough parameters\r\n").c_str()

                        
// ERR_NONICKNAMEGIVEN
// ":No nickname given"

// - Returned when a nickname parameter expected for a
// command and isn't found.


// ERR_ERRONEUSNICKNAME 
// "<nick> :Erroneus nickname"

// - Returned after receiving a NICK message which contains
// characters which do not fall in the defined set.  See
// section x.x.x for details on valid nicknames.


// ERR_NICKNAMEINUSE 
// "<nick> :Nickname is already in use"

// - Returned when a NICK message is processed that results
// in an attempt to change to a currently existing
// nickname.


// ERR_NICKCOLLISION
// "<nick> :Nickname collision KILL"

// - Returned by a server to a client when it detects a
// nickname collision (registered of a NICK that
// already exists by another server)


#endif