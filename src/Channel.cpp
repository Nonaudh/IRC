#include "Channel.hpp"
#include "error.hpp"
Channel::Channel()
{}

Channel::~Channel()
{}

Channel::Channel(int fd, std::string nameChannel, std::string password)
    : user_limit(3), topic_editable(true), name(nameChannel) 
{
        this->password = password;
        std::cout << "Le password est "<< this->password << std::endl;\
    this->invite_only = false;
    this->topic = "";
    
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

// ERR_NEEDMOREPARAMS                        
// ERR_CHANNELISFULL 
// RPL_TOPIC  
// ERR_BADCHANNELKEY


void Channel::joinChannel(int fd, e_privilege privilege, std::string passwords)
{

	//Verifier si ou non dans le channel
	//Verifier si on demande un password
	std::map <int, e_privilege > :: iterator it = this->clients.find(fd);
	if(it != this->clients.end() && it->second != INVITED)
	{
		//Il faut verifier la commande
		return;//Il est deja dans channel user ou admin;
	}
	
    if (clients.size() >= user_limit) // clients.size() sauf INVITED !!
	{
		std::cout << "Le nombre de limits de personna a ete atteintes" << std::endl;
		return;
	}
	if(!this->password.empty())
	{
		if(this->password != passwords)//Pour le mdp qui ne corresponds pas 
		return;
	}
	if(this->invite_only == true)
	{
		std::map <int, e_privilege > :: iterator it = this->clients.find(fd);//Frocement invite test avec avant si deja dans channel
		if(it == this->clients.end())
		{
			send_message(ERR_INVITEONLYCHAN(this->name), fd);
			return ;
		}
	}
	//Message si reussite
	std::cout << "Channel sans mdp" << std::endl;
	this->user_limit++;
	clients.insert(std::pair<int, e_privilege>(fd, privilege));
	std::cout << "======== CHANNEL existant ========" << std::endl;
    std::cout << "Nom du channel : " << this->name << std::endl;
    std::cout << "User limit : " << this->user_limit << std::endl;
    std::cout << "Topic éditable : " << (this->topic_editable ? "Oui" : "Non") << std::endl;
    std::cout << "Invite only : " << (this->invite_only ? "Oui" : "Non") << std::endl;
    std::cout << "JoinChannel(admin) : " << fd << std::endl;
    std::cout << "============================" << std::endl;

	send_message(RPL_TOPIC(this->name, this->topic), fd);
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

void	Channel::info(void)
{
	std::cout << "user_limit : " << user_limit << std::endl;
	std::cout << "topic_editable : " << topic_editable << std::endl;
	std::cout << "name : " << name << std::endl;
	std::cout << "password : " << password << std::endl;
	std::cout << "topic : " << topic << std::endl;
	std::cout << "invite_only : " << invite_only << std::endl;
}
