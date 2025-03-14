#include "Channel.hpp"

Channel::Channel()
{}

Channel::~Channel()
{}

Channel::Channel(int fd, std::string nameChannel)
	: user_limit(3), topic_editable(true), name(nameChannel){
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
