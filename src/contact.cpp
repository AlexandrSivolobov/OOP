#include "contact.h"
#include "validator.h"
#include <stdexcept>
#include <sstream>
#include <algorithm>

Contact::Contact() {}

Contact::Contact(const std::string& firstName, const std::string& lastName,
    const std::string& middleName, const std::string& address,
    const std::string& birthDate, const std::string& email,
    const std::string& phone)
    : firstName(firstName), lastName(lastName), middleName(middleName),
    address(address), birthDate(birthDate), email(email) {
    if (!Validator::validateName(firstName) || !Validator::validateName(lastName)) {
        throw std::invalid_argument("Invalid name format");
    }
    if (!Validator::validateEmail(email)) {
        throw std::invalid_argument("Invalid email format");
    }
    if (!Validator::validatePhone(phone)) {
        throw std::invalid_argument("Invalid phone format");
    }
    if (!Validator::validateBirthDate(birthDate)) {
        throw std::invalid_argument("Invalid birth date format or value");
    }

    phoneNumbers.push_back(phone);
}

void Contact::setFirstName(const std::string& name) {
    if (!Validator::validateName(name)) {
        throw std::invalid_argument("Invalid first name format");
    }
    firstName = name;
}

void Contact::setLastName(const std::string& name) {
    if (!Validator::validateName(name)) {
        throw std::invalid_argument("Invalid last name format");
    }
    lastName = name;
}

void Contact::setMiddleName(const std::string& name) {
    if (!name.empty() && !Validator::validateName(name)) {
        throw std::invalid_argument("Invalid middle name format");
    }
    middleName = name;
}

void Contact::setAddress(const std::string& addr) {
    address = addr;
}

void Contact::setBirthDate(const std::string& date) {
    if (!Validator::validateBirthDate(date)) {
        throw std::invalid_argument("Invalid birth date format or value");
    }
    birthDate = date;
}

void Contact::setEmail(const std::string& mail) {
    if (!Validator::validateEmail(mail)) {
        throw std::invalid_argument("Invalid email format");
    }
    email = mail;
}

void Contact::addPhoneNumber(const std::string& phone) {
    if (!Validator::validatePhone(phone)) {
        throw std::invalid_argument("Invalid phone format");
    }
    phoneNumbers.push_back(phone);
}

void Contact::removePhoneNumber(const std::string& phone) {
    auto it = std::find(phoneNumbers.begin(), phoneNumbers.end(), phone);
    if (it != phoneNumbers.end()) {
        phoneNumbers.erase(it);
    }
}

bool Contact::operator<(const Contact& other) const {
    return lastName < other.lastName ||
        (lastName == other.lastName && firstName < other.firstName) ||
        (lastName == other.lastName && firstName == other.firstName && middleName < other.middleName);
}

bool Contact::operator==(const Contact& other) const {
    return firstName == other.firstName &&
        lastName == other.lastName &&
        email == other.email;
}

std::string Contact::toString() const {
    std::ostringstream oss;
    oss << lastName << "|"
        << firstName << "|"
        << middleName << "|"
        << address << "|"
        << birthDate << "|"
        << email << "|";

    for (size_t i = 0; i < phoneNumbers.size(); ++i) {
        oss << phoneNumbers[i];
        if (i < phoneNumbers.size() - 1) {
            oss << ";";
        }
    }

    return oss.str();
}

void Contact::fromString(const std::string& data) {
    std::vector<std::string> parts;
    std::string current;
    for (char c : data) {
        if (c == '|') {
            parts.push_back(current);
            current.clear();
        }
        else {
            current += c;
        }
    }
    parts.push_back(current);

    if (parts.size() < 6) {
        throw std::invalid_argument("Invalid contact data format - not enough fields");
    }

    lastName = parts[0];
    firstName = parts[1];

    if (parts.size() > 2) {
        middleName = parts[2];
    }
    else {
        middleName = "";
    }

    address = parts[3];
    birthDate = parts[4];
    email = parts[5];

    phoneNumbers.clear();
    if (parts.size() > 6 && !parts[6].empty()) {
        std::string phones = parts[6];
        std::string currentPhone;
        for (char c : phones) {
            if (c == ';') {
                if (!currentPhone.empty()) {
                    phoneNumbers.push_back(currentPhone);
                }
                currentPhone.clear();
            }
            else {
                currentPhone += c;
            }
        }
        if (!currentPhone.empty()) {
            phoneNumbers.push_back(currentPhone);
        }
    }
}