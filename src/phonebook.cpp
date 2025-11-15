#include "phonebook.h"
#include <fstream>
#include <iostream>
#include <algorithm>

PhoneBook::PhoneBook() {}

void PhoneBook::addContact(const Contact& contact) {
    contacts.push_back(contact);
}

void PhoneBook::removeContact(size_t index) {
    if (index < contacts.size()) {
        contacts.erase(contacts.begin() + index);
    }
}

void PhoneBook::editContact(size_t index, const Contact& contact) {
    if (index < contacts.size()) {
        contacts[index] = contact;
    }
}

std::vector<Contact> PhoneBook::search(const std::string& query) {
    std::vector<Contact> result;
    for (const auto& contact : contacts) {
        if (contact.getFirstName().find(query) != std::string::npos ||
            contact.getLastName().find(query) != std::string::npos ||
            contact.getMiddleName().find(query) != std::string::npos ||
            contact.getEmail().find(query) != std::string::npos) {
            result.push_back(contact);
        }
    }
    return result;
}

void PhoneBook::sortByField(int fieldIndex) {
    switch (fieldIndex) {
    case 0: 
        std::sort(contacts.begin(), contacts.end(),
            [](const Contact& a, const Contact& b) {
                return a.getLastName() < b.getLastName();
            });
        break;
    case 1: 
        std::sort(contacts.begin(), contacts.end(),
            [](const Contact& a, const Contact& b) {
                return a.getFirstName() < b.getFirstName();
            });
        break;
    case 2: 
        std::sort(contacts.begin(), contacts.end(),
            [](const Contact& a, const Contact& b) {
                return a.getMiddleName() < b.getMiddleName();
            });
        break;
    case 3: 
        std::sort(contacts.begin(), contacts.end(),
            [](const Contact& a, const Contact& b) {
                return a.getEmail() < b.getEmail();
            });
        break;
    case 4:
        std::sort(contacts.begin(), contacts.end(),
            [](const Contact& a, const Contact& b) {
                return a.getAddress() < b.getAddress();
            });
        break;
    case 5:
        std::sort(contacts.begin(), contacts.end(),
            [](const Contact& a, const Contact& b) {
                return a.getBirthDate() < b.getBirthDate();
            });
        break;
    case 6:
        std::sort(contacts.begin(), contacts.end(),
            [](const Contact& a, const Contact& b) {
                if (a.getPhoneNumbers().empty()) return true;
                if (b.getPhoneNumbers().empty()) return false;
                return a.getPhoneNumbers()[0] < b.getPhoneNumbers()[0];
            });
        break;
    default:
        std::sort(contacts.begin(), contacts.end(),
            [](const Contact& a, const Contact& b) {
                return a.getLastName() < b.getLastName();
            });
        break;
    }
}

bool PhoneBook::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Не удалось открыть файл для записи: " << filename << std::endl;
        return false;
    }

    for (const auto& contact : contacts) {
        file << contact.toString() << std::endl;
    }

    file.close();
    return true;
}

bool PhoneBook::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Не удалось открыть файл: " << filename << std::endl;
        return false;
    }

    contacts.clear();
    std::string line;
    int count = 0;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            Contact contact;
            try {
                contact.fromString(line);
                contacts.push_back(contact);
                count++;
            }
            catch (const std::exception& e) {
                std::cout << "Ошибка при чтении контакта: " << e.what() << std::endl;
                std::cout << "Строка: " << line << std::endl;
            }
        }
    }

    std::cout << "Загружено " << count << " контактов из файла." << std::endl;

    file.close();
    return true;
}