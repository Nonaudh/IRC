#include "Channel.hpp"

Channel::Channel()
{}

Channel::~Channel()
{}

Channel::Channel(int fd, std::string nameChannel)
	: user_limit(3), topic_editable(true), name(nameChannel) {
    std::cout << "user limit : " << user_limit << std::endl;
	clients.insert(std::pair<int, e_privilege>(fd, ADMIN));
}

std::map <int , e_privilege> & Channel::getClients(void)
{
    return(this->clients);
}

void Channel::joinChannel(int fd, e_privilege privilege)
{
    if (clients.size() >= user_limit)
		return;
	clients.insert(std::pair<int, e_privilege>(fd, privilege));
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
