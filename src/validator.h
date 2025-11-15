#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>
#include <regex>

class Validator {
public:
    static bool validateName(const std::string& name);
    static bool validateEmail(const std::string& email);
    static bool validatePhone(const std::string& phone);
    static bool validateBirthDate(const std::string& date);
    static bool validateAddress(const std::string& address);
    
private:
    static bool isLeapYear(int year);
    static int daysInMonth(int month, int year);
};

#endif