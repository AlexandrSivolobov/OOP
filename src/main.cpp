#include "phonebook.h"
#include "contact.h"
#include "validator.h"
#include <iostream>
#include <string>

int main() {
    PhoneBook phonebook;

    phonebook.loadFromFile("data/contacts.txt");

    std::cout << "=== Телефонный справочник ===" << std::endl;

    int choice;
    do {
        std::cout << "\n1. Добавить контакт" << std::endl;
        std::cout << "2. Удалить контакт" << std::endl;
        std::cout << "3. Редактировать контакт" << std::endl;
        std::cout << "4. Поиск контактов" << std::endl;
        std::cout << "5. Показать все контакты" << std::endl;
        std::cout << "6. Сортировать" << std::endl;
        std::cout << "0. Выход" << std::endl;
        std::cout << "Выберите действие: ";

        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case 1: {
            std::string firstName, lastName, middleName, email, phone, address, birthDate;
            std::cout << "Введите фамилию: ";
            std::getline(std::cin, lastName);
            std::cout << "Введите имя: ";
            std::getline(std::cin, firstName);
            std::cout << "Введите отчество: ";
            std::getline(std::cin, middleName);
            std::cout << "Введите адрес: ";
            std::getline(std::cin, address);
            std::cout << "Введите дату рождения (ДД.ММ.ГГГГ): ";
            std::getline(std::cin, birthDate);
            std::cout << "Введите email: ";
            std::getline(std::cin, email);
            std::cout << "Введите телефон: ";
            std::getline(std::cin, phone);

            try {
                Contact contact(firstName, lastName, middleName, address, birthDate, email, phone);
                phonebook.addContact(contact);
                std::cout << "Контакт добавлен!" << std::endl;
            }
            catch (const std::exception& e) {
                std::cout << "Ошибка: " << e.what() << std::endl;
            }
            break;
        }
        case 2: {
            std::cout << "Введите индекс контакта для удаления: ";
            int index;
            std::cin >> index;
            phonebook.removeContact(index);
            std::cout << "Контакт удален!" << std::endl;
            break;
        }
        case 3: {
            std::cout << "Введите индекс контакта для редактирования: ";
            int index;
            std::cin >> index;

            if (index >= 0 && index < static_cast<int>(phonebook.getContacts().size())) {
                std::string firstName, lastName, middleName, email, phone, address, birthDate;
                std::cout << "Введите новую фамилию: ";
                std::cin.ignore();
                std::getline(std::cin, lastName);
                std::cout << "Введите новое имя: ";
                std::getline(std::cin, firstName);
                std::cout << "Введите новое отчество: ";
                std::getline(std::cin, middleName);
                std::cout << "Введите новый адрес: ";
                std::getline(std::cin, address);
                std::cout << "Введите новую дату рождения (ДД.ММ.ГГГГ): ";
                std::getline(std::cin, birthDate);
                std::cout << "Введите новый email: ";
                std::getline(std::cin, email);
                std::cout << "Введите новый телефон: ";
                std::getline(std::cin, phone);

                try {
                    Contact contact(firstName, lastName, middleName, address, birthDate, email, phone);
                    phonebook.editContact(index, contact);
                    std::cout << "Контакт обновлен!" << std::endl;
                }
                catch (const std::exception& e) {
                    std::cout << "Ошибка: " << e.what() << std::endl;
                }
            }
            else {
                std::cout << "Неверный индекс!" << std::endl;
            }
            break;
        }
        case 4: {
            std::string query;
            std::cout << "Введите строку для поиска: ";
            std::getline(std::cin, query);

            auto results = phonebook.search(query);
            std::cout << "Найдено " << results.size() << " контактов:" << std::endl;
            for (size_t i = 0; i < results.size(); ++i) {
                const Contact& contact = results[i];
                std::cout << i << ". " << contact.getLastName()
                    << " " << contact.getFirstName()
                    << " " << contact.getMiddleName() << std::endl;
                std::cout << "   Адрес: " << contact.getAddress() << std::endl;
                std::cout << "   Дата рождения: " << contact.getBirthDate() << std::endl;
                std::cout << "   Email: " << contact.getEmail() << std::endl;
                std::cout << "   Телефоны: ";

                const auto& phones = contact.getPhoneNumbers();
                for (size_t j = 0; j < phones.size(); ++j) {
                    std::cout << phones[j];
                    if (j < phones.size() - 1) {
                        std::cout << ", ";
                    }
                }
                std::cout << std::endl;
                std::cout << std::endl;
            }
            break;
        }
        case 5: {
            const auto& contacts = phonebook.getContacts();
            std::cout << "Все контакты:" << std::endl;
            for (size_t i = 0; i < contacts.size(); ++i) {
                const Contact& contact = contacts[i];
                std::cout << i << ". " << contact.getLastName()
                    << " " << contact.getFirstName()
                    << " " << contact.getMiddleName() << std::endl;
                std::cout << "   Адрес: " << contact.getAddress() << std::endl;
                std::cout << "   Дата рождения: " << contact.getBirthDate() << std::endl;
                std::cout << "   Email: " << contact.getEmail() << std::endl;
                std::cout << "   Телефоны: ";

                const auto& phones = contact.getPhoneNumbers();
                for (size_t j = 0; j < phones.size(); ++j) {
                    std::cout << phones[j];
                    if (j < phones.size() - 1) {
                        std::cout << ", ";
                    }
                }
                std::cout << std::endl;
                std::cout << std::endl;
            }
            break;
        }
        case 6: {
            std::cout << "1. По фамилии" << std::endl;
            std::cout << "2. По имени" << std::endl;
            std::cout << "3. По отчеству" << std::endl;
            std::cout << "4. По email" << std::endl;
            std::cout << "5. По адресу" << std::endl;
            std::cout << "6. По дате рождения" << std::endl;
            std::cout << "7. По телефону (первый)" << std::endl;
            std::cout << "Выберите поле для сортировки: ";
            int field;
            std::cin >> field;
            phonebook.sortByField(field - 1);
            std::cout << "Сортировка выполнена!" << std::endl;
            break;
        }
        case 0:
            std::cout << "Готово, данные сохранены" << std::endl;
            phonebook.saveToFile("data/contacts.txt");
            break;
        default:
            std::cout << "Неверный выбор!" << std::endl;
        }
    } while (choice != 0);

    return 0;
}