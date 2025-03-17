#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>

enum	e_privilege
{
	INVITE,
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
        Channel(int fd, std::string nameChannel);
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

		void	info(void);
        // //Determiner le topic(si bool mdfTopic)
        // void setTopic(std::string const& newTopic)
        // std::string const& getTopic(void)const;
        // //Determiner le mots de pass dans le Channel
        // void setPassword(std::string const& newPassword);
        // std::string const& getPassword(void)const;
        // //Determiner le nombre dans le Channel
        // void getLimitPeople(int newLimitPeople);
        // int setLimitPeople(void)const;
        // //Retirer les droits admin
        // void changePrivil(int id)const;
        std::map <int , e_privilege>& getClients(void);

        size_t nbrPeople();
        void joinChannel(int socketFd, e_privilege privilege);
};