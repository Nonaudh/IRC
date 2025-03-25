#include "Channel.hpp"
#include "error.hpp"
#include "Server.hpp"

Channel::Channel()
{}

Channel::~Channel()
{}

Channel::Channel(int fd, std::string nameChannel, std::string password)
    : user_limit(3), topic_editable(true), name(nameChannel)
{
	this->password = password;
	std::cout << "Le password est "<< this->password << std::endl;
    this->invite_only = false;
	nameChannel.erase(nameChannel.begin());
    this->topic ="";
    
    std::cout << "======== CHANNEL CRÉÉ ========" << std::endl;
    std::cout << "Nom du channel : " << this->name << std::endl;
    std::cout << "User limit : " << this->user_limit << std::endl;
    std::cout << "Topic éditable : " << (this->topic_editable ? "Oui" : "Non") << std::endl;
    std::cout << "Invite only : " << (this->invite_only ? "Oui" : "Non") << std::endl;
    std::cout << "Premier client (admin) : " << fd << std::endl;
    std::cout << "============================" << std::endl;
    
    clients.insert(std::pair<int, e_privilege>(fd, ADMIN));
}

std::map <int , e_privilege> & Channel::getClients(void)
{
    return(this->clients);
}

std::string	list_nick_channel(Channel& chan, Server& serv)
{
	std::string	nicknames;
	std::map<int, e_privilege>&	clis = chan.getClients();

	for (std::map<int, e_privilege>::iterator it = clis.begin(); it != clis.end(); ++it)
	{
		nicknames = nicknames + serv.findClient(it->first).getNick() + " ";
	}
	return (nicknames);
}

void	actualise_name_reply(Channel& chan, Server& serv, Client& cli)
{
	std::map<int, e_privilege>&	clients = chan.getClients();

	for (std::map<int, e_privilege>::iterator it = clients.begin(); it != clients.end(); ++it)
	{
		if (it->second != INVITED)
			send_message(RPL_NAMEREPLY(cli.getNick(), chan.get_name(), list_nick_channel(chan, serv).c_str()), it->first);
	}
}

void Channel::joinChannel(Client& client, e_privilege privilege, std::string passwords, Server& serv)
{
	std::map <int, e_privilege > :: iterator it = this->clients.find(client.getFd());

	if (it != this->clients.end() && it->second != INVITED)
	{
		send_message(ERR_USERONCHANNEL(client.getNick(), this->name), client.getFd());
		return;
	}
	
    if (size() >= user_limit)
	{
		send_message(ERR_CHANNELISFULL(CLIENT(client.getNick(), client.getUser()), this->name), client.getFd());
		return ;
	}
	if (!this->password.empty())
	{
		if(this->password != passwords)
		{
			send_message(ERR_BADCHANNELKEY(CLIENT(client.getNick(), client.getUser()), this->name), client.getFd());
			return ;
		}
	}
	if (this->invite_only == true)
	{
		std::map <int, e_privilege > :: iterator it = this->clients.find(client.getFd());
		if(it == this->clients.end())
		{
			send_message(ERR_INVITEONLYCHAN(CLIENT(client.getNick(), client.getUser()), this->name), client.getFd());
			return ;
		}
	}
	if(it != clients.end())
		it->second = USER;
	else
		clients.insert(std::pair<int, e_privilege>(client.getFd(), privilege));

	send_message(RPL_JOIN(CLIENT(client.getNick(), client.getUser()), this->name), client.getFd());
	actualise_name_reply(*this, serv, client);
}

void Channel::setMdfTopic(bool mdf)
{
	this->topic_editable = mdf;
}

bool Channel::getMdfTopic()const
{
	return (topic_editable);
}

void Channel::set_password(std::string pass)
{
	this->password = pass;
}

std::string Channel::get_password(void)const
{
	return (this->password);
}

void Channel::set_user_limit(size_t limit)
{
	this->user_limit = limit;
}

size_t Channel::get_user_limit(void)const
{
	return (this->user_limit);
}

void Channel::set_topic_editable(bool edit)
{
	this->topic_editable = edit;
}

bool Channel::get_topic_editable(void)const
{
	return (this->topic_editable);
}

void	Channel::set_topic(std::string topic)
{
	this->topic = topic;
}

std::string	Channel::get_topic(void)const
{
	return (this->topic);
}

void Channel::set_invite_only(bool invit)
{
	this->invite_only = invit;
}

bool Channel::get_invite_only(void)const
{
	return (this->invite_only);
}

std::string	Channel::get_name(void)
{
	return (this->name);
}

void	Channel::info(void)
{
	std::cout << "user_limit : " << user_limit << std::endl;
	std::cout << "topic_editable : " << topic_editable << std::endl;
	std::cout << "name : " << name << std::endl;
	std::cout << "password : " << password << std::endl;
	std::cout << "topic : " << topic << std::endl;
	std::cout << "invite_only : " << invite_only << std::endl;
}

size_t	Channel::size(void)
{
	size_t	size = 0;
	std::map<int, e_privilege>::iterator	it;

	for (it = clients.begin(); it != clients.end(); ++it)
	{
		if (it->second != INVITED)
			++size;
	}
	return (size);
}
