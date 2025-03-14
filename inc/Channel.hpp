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
        std::string password;
        size_t user_limit;
        bool topic_editable;
        std::string name;
    public:
		Channel();
        Channel(int fd, std::string nameChannel);
        virtual ~Channel();
        void setMdfTopic(bool mdf);
        bool getMdfTopic()const;
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