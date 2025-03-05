#pragma once
#include <iostream>
#include <string>
#include <vector>

class Channel
{
    private:
        //Mise en place de tous les arguments demander dans le sujet
        std::vector <int> socketFdClient; //client
        std::vector <int>socketInvite;//invite
        std::vector <int>socketAdmin;
        std::string password;
        int nbr_limit_people;
        bool topic_editable;
        //On peux ou non modifier 
        std::string name;
    public:
         Channel();
        //MIse en place des constructeur de la class
        Channel(int fd, std::string nameChannel);//Default
        virtual ~Channel();//Destructeur    
        //Modifier le bool
        void setMdfTopic();
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

        //Utilils pour la class Channel
        size_t nbrPeople();
        //Join Channel
        void joinChannel(int privilege, int socketFd);
};