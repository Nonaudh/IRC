#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Client.hpp"

class	Server;

enum	e_privilege
{
	INVITED,
	USER,
	ADMIN,
};


class Channel
{
    private:
        std::map<int, e_privilege> clients;
        size_t user_limit;
        bool topic_editable;
        std::string name;
        std::string password;
		std::string	topic;
		bool invite_only;
    public:
		Channel();
        Channel(int fd, std::string nameChannel, std::string password);
        virtual ~Channel();

		void set_password(std::string pass);

        void set_user_limit(size_t limit);

        void set_topic_editable(bool edit);
        bool get_topic_editable(void)const;

		void	set_topic(std::string topic);
		std::string	get_topic(void)const;

		void set_invite_only(bool invit);

		std::string	get_name(void);

		void	info(void);

        std::map <int , e_privilege>& getClients(void);
        
		size_t	size(void);
        void joinChannel(Client& client, e_privilege privilege, std::string password, Server& serv);
};

void	send_message(std::string str, int fd);

int		searchNbrChannels(std::vector<std::string>& params);