#include "validator.h"
#include <cctype>
#include <algorithm>
#include <sstream>

bool Validator::validateName(const std::string& name) {
    if (name.empty()) return true;

    if (name[0] == '-' || name[name.length() - 1] == '-') {
        return false;
    }

    if (name[0] == ' ' || name[name.length() - 1] == ' ') {
        return false;
    }

    for (char c : name) {
        if (c < 0) {
            continue;
        }
        if (!std::isalnum(c) && c != '-' && c != ' ') {
            return false;
        }
    }

    for (char c : name) {
        if (std::isspace(c)) continue;
        if (std::isalpha(c) || c < 0) {
            return true;
        }
        return false;
    }

    return false;
}

bool Validator::validateEmail(const std::string& email) {
    if (email.empty()) return false;
    
    size_t atPos = email.find('@');
    if (atPos == std::string::npos || atPos == 0 || atPos == email.length() - 1) {
        return false;
    }
    
    std::string user = email.substr(0, atPos);
    std::string domain = email.substr(atPos + 1);
    
    if (user.empty() || domain.empty()) return false;

    for (char c : user) {
        if (!std::isalnum(c)) return false;
    }

    for (char c : domain) {
        if (!std::isalnum(c) && c != '.') return false;
    }
    
    return true;
}

bool Validator::validatePhone(const std::string& phone) {
    std::string cleanPhone;
    for (char c : phone) {
        if (std::isdigit(c)) {
            cleanPhone += c;
        }
    }
    if ((cleanPhone[0] == '7' || cleanPhone[0] == '8') && cleanPhone.length() == 11) {
        return true;
    }
    
    return false;
}

bool Validator::validateBirthDate(const std::string& date) {
    if (date.empty()) return true;

    if (date.length() != 10 || date[2] != '.' || date[5] != '.') {
        return false;
    }
    
    int day, month, year;
    try {
        day = std::stoi(date.substr(0, 2));
        month = std::stoi(date.substr(3, 2));
        year = std::stoi(date.substr(6, 4));
    } catch (...) {
        return false;
    }
    
    if (year < 1900 || year > 2025) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > daysInMonth(month, year)) return false;
    
    return true;
}

bool Validator::validateAddress(const std::string& address) {
    return true;
}

bool Validator::isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int Validator::daysInMonth(int month, int year) {
    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return isLeapYear(year) ? 29 : 28;
        default:
            return 0;
    }
}