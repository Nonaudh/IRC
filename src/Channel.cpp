#include "Channel.hpp"

Channel::Channel(){}

Channel::~Channel(){
    std::cout << "Destructor called" << std::endl;
}
Channel::Channel(int fd, std::string nameChannel)
	: user_limit(3), topic_editable(true), name(nameChannel){
    std::cout << "user limit : " << user_limit << std::endl;
	clients.insert(std::pair<int, e_privilege>(fd, USER));
}

//Mise en place des methodes demande

//Modifier le bool
// void Channel::setMdfTopic()
// {
//     if(this-> mdfTopic== false)
//         this->mdfTopic =true;
//     else
//         this->mdfTopic= false;
// }
// bool Channel::getMdfTopic()const
// {
//     return(this->mdfTopic);
// }

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

void Channel::joinChannel(int fd, e_privilege privilege)
{
    if (clients.size() >= user_limit)
		return;
	clients.insert(std::pair<int, e_privilege>(fd, privilege));
}
