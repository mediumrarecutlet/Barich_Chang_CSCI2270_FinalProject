#ifndef PHONEBOOK_CPP
#define PHONEBOOK_CPP

#include <sstream>
#include <iostream>

Contact *PhoneBook::SearchPhoneBook(string name)
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
    

}
void PhoneBook::addContact(string name, string number, string email)
{
        if(root == NULL){
        root = new struct Contact(name, number, email);
    }
    else{
        PhoneBook* current = root;

        while (current != NULL){
            if(current->name >= name){
                if (current->left == NULL){
                    current->left = new struct Contact(name, number, email);
                    current->left->parent = current;
                    current = NULL;
                }
                else{
                    current = current->left;
                }
            }
            else if(current->name <= name){
                if (current->right == NULL){
                    current->right = new struct Contact(name, number, email);
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
    current = searchMovieTree(title);
    if(current != NULL){
        if (current->right != NULL && current->left != NULL){
            Contact* node = current->right;

            while(node->left != NULL){
                node = node->left;
            }
            current->number = node->name;
            current->name = node->name;
            current->email = node->email;

            if(node->rightChild != NULL){
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
	contactsFile.open(file);
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
	ofstream outputFile;
	outputFile.open(file);
	if(outputFile.is_open())
	{
		for(int i = 0; i < contacts.size() - 1; i++)
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

#endif
