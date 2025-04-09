#include "Channel.hpp"
#include "error.hpp"
#include "Server.hpp"

Channel::Channel()
{}

Channel::~Channel()
{}

Channel::Channel(int fd, std::string nameChannel, std::string password)
    : user_limit(-1), topic_editable(true), name(nameChannel)
{
	this->password = password;
    this->invite_only = false;
	nameChannel.erase(nameChannel.begin());
    this->topic = "";
    clients.insert(std::pair<int, e_privilege>(fd, ADMIN));
}

std::map <int , e_privilege> & Channel::getClients(void)
{
    return(this->clients);
}

void Channel::set_password(std::string pass)
{
	this->password = pass;
}

void Channel::set_user_limit(size_t limit)
{
	this->user_limit = limit;
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

std::string	Channel::get_name(void)
{
	return (this->name);
}

std::string Channel::getChannelModeReply() {
	std::string modes = "+";
	std::vector<std::string> params;

	if (invite_only) modes += "i";
	if (topic_editable) modes += "t";
	if (!password.empty()) {
		modes += "k";
		params.push_back(password);
	}
	if (user_limit > 0) {
		modes += "l";
		params.push_back(int_to_string(user_limit));
	}

	std::ostringstream reply;
	reply << modes;

	for (std::vector<std::string>::iterator it = params.begin(); it != params.end(); ++it)
	{
		reply << " " << it.base();
	}

	return reply.str();
}

int	Channel::size(void)
{
	int	size = 0;
	std::map<int, e_privilege>::iterator	it;

	for (it = clients.begin(); it != clients.end(); ++it)
	{
		if (it->second != INVITED)
			++size;
	}
	return (size);
}

int	searchNbrChannels(std::vector<std::string>& params)
{
	int	countMdp = 0;
	std::string	c = "#&";

	for (std::vector<std::string>::iterator it = params.begin(); it != params.end(); ++it)
	{
		if (c.find(*it->begin()) != std::string::npos)
			countMdp++;
	}
	return (countMdp);
}