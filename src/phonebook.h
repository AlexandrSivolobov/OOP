#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#include "contact.h"
#include <vector>
#include <string>
#include <functional>

class PhoneBook {
public:
    PhoneBook();
    
    void addContact(const Contact& contact);
    void removeContact(size_t index);
    void editContact(size_t index, const Contact& contact);
    
    const std::vector<Contact>& getContacts() const { return contacts; }
    
    std::vector<Contact> search(const std::string& query);
    void sortByField(int fieldIndex);

    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);
    
private:
    std::vector<Contact> contacts;
};

#endif