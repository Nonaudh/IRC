#ifndef ERROR_HPP
# define ERROR_HPP

// #define CLIENT(nick, user) (std::string(nick) + "!" + std::string(user) + "@localhost").c_str()

// #define RPL_JOIN(client, channel) (":" + std::string(client) + " JOIN " + std::string(channel) + "\r\n").c_str()

// #define ERR_NONICKNAMEGIVEN ":No nickname given\r\n"

// #define ERR_NICKNAMEINUSE(nick) (std::string(nick) + " :Nickname is already in use\r\n").c_str()

// #define ERR_NOPRIVILEGES ":Permission Denied- You're not an IRC operator\r\n"

// #define ERR_NOSUCHCHANNEL(channel) (std::string(channel) + " :No such channel\r\n").c_str()
                        
// #define ERR_CHANOPRIVSNEEDED(channel) (std::string(channel) + " :You're not channel operator\r\n").c_str()

// #define ERR_NOTONCHANNEL(channel) (std::string(channel) + " :You're not on that channel\r\n").c_str()
                       
// #define ERR_NOSUCHNICK(nick) (std::string(nick) + " :No such nick/channel\r\n").c_str()

// #define ERR_NEEDMOREPARAMS(cmd) (std::string(cmd) + " :Not enough parameters\r\n").c_str()

// #define ERR_UNKNOWNMODE(mode) (std::string(mode) + " :is unknown mode to me\r\n").c_str()

// //POur join

// #define ERR_INVITEONLYCHAN(channel) (std::string(channel) + " :Cannot join channel (+i)\r\n").c_str()

// #define ERR_NOTONCHANNEL(channel) (std::string(channel) + " :You're not on that channel\r\n").c_str()

// #define ERR_USERONCHANNEL(user, channel) (std::string(user) + " " + std::string(channel) + " :is already on channel\r\n").c_str()

// #define RPL_TOPIC(channel, topic) (std::string(channel) + " :" + std::string(topic) + "\r\n").c_str()

// #define RPL_INVITING(channel, nick) (std::string(channel) + " " + std::string(nick) + "\r\n").c_str()


#define CLIENT(nick, user)(nick + "!" + user + "@localhost")
#define PRIVMSG(client, target, message)(":" + client + " PRIVMSG " + target + " :" + message + "\r\n")
#define NOTICE(client, target, message)(":" + client + " NOTICE " + target + " :" + message + "\r\n")

#define RPL_JOIN(client, channel)(":" + client + " JOIN " + channel + "\r\n")
#define RPL_PART(client, channel)(":" + client + " PART " + channel + "\r\n")
#define RPL_MODE(client, channel, mode, name)(":" + client + " MODE " + channel + " " + mode + " " + name + "\r\n")
#define RPL_KICK(client, channel, target)(":" + client + " KICK " + channel + " " + target + "\r\n")
#define RPL_INVITERCVR(client, invitee, channel)(":" + client + " INVITE " + invitee + " " + channel + "\r\n")
#define RPL_NICK(oldNick, newNick)(":" + oldNick + " NICK " + newNick + "\r\n")
#define RPL_TOPIC(client, channel, topic)(":" + client + " TOPIC " + channel + " :" + topic + "\r\n")
#define RPL_WELCOME(nickname)(": 001 " + nickname + " :Welcome to the IRC world, " + nickname + "\r\n")
#define RPL_NOTOPIC(client, channel)(": 331 " + client + " " + channel + " :No topic is set\r\n")
#define RPL_SEETOPIC(client, channel, topic)(": 332 " + client + " " + channel + " :" + topic + "\r\n")
#define RPL_INVITESNDR(client, invitee, channel)(": 341 " + client + " " + invitee + " " + channel + "\r\n")
#define RPL_NAMEREPLY(nick, channel, nicknames)(": 353 " + nick + " = " + channel + " :" + nicknames + "\r\n")

#define ERR_TOOMUCHPARAMS(client, cmd)(client + " " + cmd + " :Too much parameters\r\n")
#define ERR_USERONCHANNEL(nick, channel)(": 303 " + nick + " " + channel + " :is already on channel\r\n")
#define ERR_NOSUCHNICK(client, nickname)(": 401 " + client + " " + nickname + " :No such nickname\r\n")
#define ERR_NOSUCHCHANNEL(channel)(": 403 " + channel + " :No such channel\r\n")
#define ERR_CANNOTSENDTOCHAN(client, channel)(": 404 " + client + " " + channel + " :Cannot send to channel\r\n")
#define ERR_NOTEXTTOSEND(client)(": 412 " + client + " :No text to send\r\n")

#define ERR_NONICKNAMEGIVEN(client, nick)(": 431 " + client + " " + nick + " :No nickname given\r\n")

#define ERR_ERRONEUSNICKNAME(client, nickname)(": 432 " + client + " " + nickname + " :Erroneus nickname\r\n")
#define ERR_NICKNAMEINUSE(client, nick)(": 433 * " + client + " " + nick + " :Nickname is already in use\r\n")
#define ERR_ERRONEUSUSERNAME(client, username)(": 432 " + client + " " + username + " :Erroneus username\r\n")
#define ERR_USERNAMEINUSE(client, username)(": 433 * " + client + " " + username + " :Username is already in use\r\n")
#define ERR_NORECIPIENT(client, command)(": 411 " + client + " " + command + " :No recipient given\r\n")

#define ERR_USERNOTINCHANNEL(client, nick, channel)(": 441 " + client + " " + nick + " " + channel + " :They aren't on that channel\r\n")
#define ERR_NOTONCHANNEL(client, channel)(": 442 " + client + " " + channel + " :Not on that channel\r\n")
#define ERR_NOTREGISTERED()(": 451 :You have not registered\r\n")
#define ERR_NEEDMOREPARAMS(client, cmd)(": 461 " + client + " " + cmd + " :Not enough parameters\r\n")
#define ERR_ALREADYREGISTRED(client)(": 462 " + client + " :You may not reregister\r\n")
#define ERR_PASSWDMISMATCH(client)(": 464 " + client + " :Password incorrect\r\n")
#define ERR_KEYSET(channel)(": 467 " + channel + " :Channel key already set\r\n")
#define ERR_CHANNELISFULL(client, channel)(": 471 " + client + " " + channel + " :Cannot join channel (+l)\r\n")
#define ERR_UNKNOWNMODE(client, mode)(": 472 " + client + " " + mode + " :is unknown mode char to me\r\n")
#define ERR_INVITEONLYCHAN(client, channel)(": 473 " + client + " " + channel + " :Cannot join channel (+i)\r\n")
#define ERR_BADCHANNELKEY(client, channel)(": 475 " + client + " " + channel + " :Cannot join channel (+k)\r\n")
#define ERR_NOCHANMODES(channel)(": 477 " + channel + " :Channel doesn't support modes\r\n")
#define ERR_CHANOPRIVSNEEDED(client, channel)(": 482 " + client + " " + channel + " :You're not channel operator\r\n")


// ERR_INVITEONLYCHAN            
// ERR_CHANNELISFULL 
// RPL_TOPIC  
// ERR_BADCHANNELKEY
                        
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
