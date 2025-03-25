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

        void setMdfTopic(bool mdf);
        bool getMdfTopic(void)const;

		void set_password(std::string pass);
		std::string get_password(void)const;

        void set_user_limit(size_t limit);
        size_t get_user_limit(void)const;

        void set_topic_editable(bool edit);
        bool get_topic_editable(void)const;

		void	set_topic(std::string topic);
		std::string	get_topic(void)const;

		void set_invite_only(bool invit);
		bool get_invite_only(void)const;

		std::string	get_name(void);

		void	info(void);

        std::map <int , e_privilege>& getClients(void);

		size_t	size(void);
        void joinChannel(Client& client, e_privilege privilege, std::string password, Server& serv);
};

void	send_message(std::string str, int fd);
