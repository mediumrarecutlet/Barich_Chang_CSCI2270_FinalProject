#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#include <sstream>
#include <iostream>
#include <vector>

struct Contact {
    std::string number;
    std::string name;
    std::string email;
    int search;
    int favorite; // 1 or 0
    Contact *parent;
    Contact *left;
    Contact *right;

    Contact(){};

    Contact(std::string in_name,std::string in_number, std::string in_email, int in_search, int in_favorite)
    {
        number = in_number;
        name = in_name;
        email = in_email;
        search = in_search;
        favorite = in_favorite;
        parent = NULL;
        left = NULL;
        right = NULL;
    }
};

class PhoneBook
{
public:
    PhoneBook();
    ~PhoneBook();
    Contact* SearchPhoneBook(std::string name);
    void addContact(std::string name, std::string number, std::string email, int search, int favorite);
    void deleteContact(std::string name);
    void editContact(std::string name1, std::string name2, std::string number, std::string email);
    void printPhoneBook();
    void loadContacts();
    void saveContacts();
    void Favorites();
    void updateSearchCount(std::string name);
    void ChangeFavorite(std::string name, int favorite);
    void Recent();


private:
	std::string file;
    Contact *root;
    Contact* search(std::string name, Contact *node);
    std::vector<Contact*> contacts;
    std::vector<Contact*> recent;
    void saveContacts(Contact *node);
    void printFavorites(Contact *node);
    void printPhone(Contact* current);
};
#endif // PHONEBOOK_H
