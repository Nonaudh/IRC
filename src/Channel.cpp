#include "Channel.hpp"

//MIse en place du constructeur par default
Channel::~Channel(){
    std::cout << "Destruct Channel ok " << std::endl;
}
Channel::Channel():nbr_limit_people(2), mdfTopic(true), name("Je ne sais pas avoir"){
    std::cout << "camarche" << std::endl;
    //Determiner 
}

//Mise en place des methodes demande 

//Modifier le bool
void Channel::setMdfTopic()
{
    if(this-> mdfTopic== false)
        this->mdfTopic =true;
    else 
        this->mdfTopic= false;
}
bool Channel::getMdfTopic()const
{  
    return(this->mdfTopic);
}

// void Channel::setTopic(std::string const& newTopic)//Determiner le topic(si bool mdfTopic
// {
//     if(this->mdfTopic==false)
//     {
//         //IL n'y a que les admin qui peuvent changer le topic
//         std::vector<int>::iterator it = socketAdmin.find(this->)
//         if(it == socketAdmin.end())
//             return
//     }
//     this->topic = newTopic;
// }
// std::string const& Channel::getTopic(void)const
// {
//     return(this->Topic);
// }
// //Determiner le mots de pass dans le Channel 
// void Channel::setPassword(std::string const& newPassword)//Il n'y a que les admins qui peux changer le programme 
// {
//     std::vector<int>:: iterator it = socketAdmin.find()
//     if(it != socketAdmin.end())
//         this->password = newPassword;
// }
// std::string const& Channel::getPassword(void)const
// {
//     return(this->password);
// }
// //Determiner le nombre dans le Channel
// void Channel::getLimitPeople(int newLimitPeople)
// {
//     return(this->nbr_limit_people);
// }
// int Channel::setLimitPeople(void)const
// {
//     std::vector<int>:: iterator it = socketAdmin.find()
//     if(it != socketAdmin.end())
//         this->nbr_limit_people = newLimitPeople;
// }
// //Retirer les droits admin  
// void Channel::changePrivil(int id)const
// {   
//     std::vector<int>:: iterator it = socketAdmin.find()
//     if(it != socketAdmin.end())
//     {
//         std::vector<int>:: const_iterator const_it = socketAdmin.find()
//         if(const_it != socketAdmin.end())
//     }
// }

//Mise en place du join Channel
void Channel::joinChannel(int privilege, int fd)
{
    size_t i =this->nbrPeople();
    if((int)i > nbr_limit_people)   
        return;
    if(privilege == 0)
        this->socketAdmin.push_back(fd);
    if(privilege == 1)
        this->socketFdClient.push_back(fd);
    if(privilege == 2)
        this->socketInvite.push_back(fd);
    else
        std::cout << "TU fais quoi ce n'est pas possible teuteu" << std::endl;
}

//Fonction qui sont utilies 
size_t Channel::nbrPeople()
{
    size_t nombreElements = socketFdClient.size();
    nombreElements += socketAdmin.size();
    nombreElements += socketInvite.size();
    return(nombreElements);
}