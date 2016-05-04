#ifndef PHONEBOOK_CPP
#define PHONEBOOK_CPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>


#include "PhoneBook.h"
using namespace std;
PhoneBook::PhoneBook()
{
	loadContacts();
}
PhoneBook::~PhoneBook()
{

}

Contact* PhoneBook::SearchPhoneBook(string name)
{
    Contact* current = root;

    while (current != NULL){
        if(current->name > name){
            current = current->left;
        }
        else if(current->name < name){
            current = current->right;
        }
        else if(current->name == name){
			recent.push_back(current);
            return current;
        }
    }
    return NULL;

}
void PhoneBook::addContact(string name, string number, string email, int search, int favorite)
{
        if(root == NULL){
        root = new struct Contact(name, number, email, search, favorite);
    }
    else{
        Contact* current = root;

        while (current != NULL){
            if(current->name >= name){
                if (current->left == NULL){
                    current->left = new struct Contact(name, number, email, search, favorite);
                    current->left->parent = current;
                    current = NULL;
                }
                else{
                    current = current->left;
                }
            }
            else if(current->name <= name){
                if (current->right == NULL){
                    current->right = new struct Contact(name, number, email, search, favorite);
                    current->right->parent = current;
                    current = NULL;
                }
                else{
                    current = current->right;
                }
            }
        }
    }
}
void PhoneBook::deleteContact(string name)
{
    Contact* current = root;
    current = SearchPhoneBook(name);
    if(current != NULL){
        if (current->right != NULL && current->left != NULL){
            Contact* node = current->right;

            while(node->left != NULL){
                node = node->left;
            }
            current->number = node->name;
            current->name = node->name;
            current->email = node->email;

            if(node->right != NULL){
                if (node->parent->left == node)
                    node->parent->left = node->right;
                if (node->parent->right == node)
                    node->parent->right = node->right;
                node->right->parent = node->parent;
            }
            else{
                if (node->parent->left == node)
                    node->parent->left = NULL;
                if (node->parent->right == node)
                    node->parent->right = NULL;
            }

            delete node;
        }
        else if(current->right == NULL && current->left != NULL){
            if (current != root){
                if (current->parent->left == current){
                    current->parent->left = current->left;
                }
                else if (current->parent->right == current){
                    current->parent->right = current->left;
                }
            }
            else{
                root = current->left;
            }
            current->left->parent = current->parent;
            delete current;
        }
        else if(current->right != NULL && current->left == NULL){
            if (current != root){
                if (current->parent->left == current){
                    current->parent->left = current->right;
                }
                else if (current->parent->right == current){
                    current->parent->right = current->right;
                }
            }
            else{
                root = current->right;
            }
            current->right->parent = current->parent;
            delete current;
        }
        else{
            if (current != root){
                if (current->parent->left == current){
                    current->parent->left = NULL;
                }
                else if(current->parent->right == current){
                    current->parent->right = NULL;
                }
            }
            else{
                root = NULL;
            }
            delete current;
        }
    }
}
void PhoneBook::loadContacts()
{
	ifstream contactsFile;
	string data;
	contactsFile.open("Contacts.txt");
	if(contactsFile.is_open())
	{
		while(getline(contactsFile, data))
		{
			stringstream ss(data);
			string comma;
			std::string name;
			std::string email;
			std::string number;
			int search;
			int favorite;

			for(int i = 0; (getline(ss,comma,',')); i++)
			{
				if(i % 5 == 0)
				{
					name = comma;
				}
				else if(i % 5 == 1)
				{
					number = comma;
				}
				else if(i % 5 == 2)
				{
					email = comma;
				}
				else if(i % 5 == 3)
				{
					search = atoi(comma.c_str());
				}
				else if(i % 5 == 4)
				{
					search = atoi(comma.c_str());
				}
			}
			addContact(name, number, email, search, favorite);
		}
	}
	else
	{
	}
}
void PhoneBook::saveContacts()
{
	saveContacts(root);
	ofstream outputFile("Contacts.txt");
	if(outputFile.is_open())
	{
		for(int i = 0; i < contacts.size(); i++)
		{
			outputFile << contacts[i] -> name << "," << contacts[i] -> number << "," << contacts[i] -> email << ",";
			outputFile << contacts[i] -> search << "," << contacts[i] -> favorite << std::endl;

		}
		outputFile.close();
	}
	contacts.clear();
}
void PhoneBook::saveContacts(Contact *node)
{

	Contact *nextNode;
	if(node -> left != NULL)
	{
		nextNode = node -> left;
		saveContacts(nextNode);

	}
	contacts.push_back(node);
	if(node -> right != NULL)
	{
		nextNode = node -> right;
		saveContacts(nextNode);
	}


}
void PhoneBook::updateSearchCount(std::string name)
{
	Contact *found = SearchPhoneBook(name);
	found -> search++;
}
void PhoneBook::Favorites()
{
	std::cout << "-----FAVORITES-----" << std::endl;
	printFavorites(root);
}
void PhoneBook::printFavorites(Contact *node)
{
	Contact *nextNode;
	if(node -> left != NULL)
	{
		nextNode = node -> left;
		printFavorites(nextNode);

	}
	if(node -> favorite == 1)
	{
		std::cout << node -> name << "," << node -> number << "," << node -> email << std::endl;
	}
	if(node -> right != NULL)
	{
		nextNode = node -> right;
		printFavorites(nextNode);
	}
}
void PhoneBook::ChangeFavorite(std::string name, int favorite)
{
	Contact *found = SearchPhoneBook(name);
	found -> favorite = favorite;
}
void PhoneBook::Recent()
{
	std::cout << "-----RECENT-----" << std::endl;
	for(int i = recent.size() - 1; i >= 0; i--)
	{
		std::cout << recent[i] -> name << std::endl;
	}
}
void PhoneBook::editContact(std::string name1, std::string name2, std::string number, std::string email)
{
    Contact *change = SearchPhoneBook(name1);
    if(change != NULL){
    change->name = name2;
    change->number = number;
    change->email = email;
    cout<<"Changes Successfully Made"<<endl;
    }
    else{
        cout<<"No Contact Was Found"<<endl;
    }
}

void PhoneBook::printPhone(Contact* current)
{
    if(current->left!=NULL){
        printPhone(current->left);
    }
    cout<<"Name: "<<current->name<<endl;
    cout<<"Number: "<<current->number<<endl;
    cout<<"Email: "<<current->email<<endl;
    if(current->right!=NULL){
        printPhone(current->right);
    }
}

void PhoneBook::printPhoneBook()
{

    if (root != NULL){
		cout<<"-----Contacts-----"<<endl;
        printPhone(root);
    }
}

#endif
