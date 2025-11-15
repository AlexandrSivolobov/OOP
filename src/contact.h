#ifndef CONTACT_H
#define CONTACT_H

#include <string>
#include <vector>
#include <memory>

class Contact {
public:
    Contact();
    Contact(const std::string& firstName, const std::string& lastName, 
            const std::string& middleName, const std::string& address, 
            const std::string& birthDate, const std::string& email, 
            const std::string& phone);
    
    const std::string& getFirstName() const { return firstName; }
    const std::string& getLastName() const { return lastName; }
    const std::string& getMiddleName() const { return middleName; }
    const std::string& getAddress() const { return address; }
    const std::string& getBirthDate() const { return birthDate; }
    const std::string& getEmail() const { return email; }
    const std::vector<std::string>& getPhoneNumbers() const { return phoneNumbers; }
    
    void setFirstName(const std::string& name);
    void setLastName(const std::string& name);
    void setMiddleName(const std::string& name);
    void setAddress(const std::string& addr);
    void setBirthDate(const std::string& date);
    void setEmail(const std::string& mail);
    
    void addPhoneNumber(const std::string& phone);
    void removePhoneNumber(const std::string& phone);
    
    bool operator<(const Contact& other) const;
    bool operator==(const Contact& other) const;
    
    std::string toString() const;
    void fromString(const std::string& data);
    
private:
    std::string firstName;
    std::string lastName;
    std::string middleName;
    std::string address;
    std::string birthDate;
    std::string email;
    std::vector<std::string> phoneNumbers;
};

#endif 