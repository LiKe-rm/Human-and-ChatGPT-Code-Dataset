#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#ifdef LOTS_OF_VECTORS
// 使用六个std::vector<std::string>存储电话簿项
struct PhoneBookItem {
    std::vector<std::string> firstName;
    std::vector<std::string> lastName;
    std::vector<std::string> homePhone;
    std::vector<std::string> mobilePhone;
    std::vector<std::string> homeAddress;
    std::vector<std::string> email;
};

void fillPhoneBookItem(PhoneBookItem& item) {
    std::string firstName, lastName, homePhone, mobilePhone, homeAddress, email;
    std::cout << "Please enter first name: ";
    std::getline(std::cin, firstName);
    item.firstName.push_back(firstName);

    std::cout << "Please enter last name: ";
    std::getline(std::cin, lastName);
    item.lastName.push_back(lastName);

    std::cout << "Please enter home phone: ";
    std::getline(std::cin, homePhone);
    item.homePhone.push_back(homePhone);

    std::cout << "Please enter mobile phone: ";
    std::getline(std::cin, mobilePhone);
    item.mobilePhone.push_back(mobilePhone);

    std::cout << "Please enter home address: ";
    std::getline(std::cin, homeAddress);
    item.homeAddress.push_back(homeAddress);

    std::cout << "Please enter email: ";
    std::getline(std::cin, email);
    item.email.push_back(email);
}

void printPhoneBookItem(const PhoneBookItem& item) {
    std::cout << "First name: " << item.firstName[0] << std::endl;
    std::cout << "Last name: " << item.lastName[0] << std::endl;
    std::cout << "Home phone: " << item.homePhone[0] << std::endl;
    std::cout << "Mobile phone: " << item.mobilePhone[0] << std::endl;
    std::cout << "Home address: " << item.homeAddress[0] << std::endl;
    std::cout << "Email: " << item.email[0] << std::endl;
}

void sortPhoneBookItem(PhoneBookItem& item) {
    for (int i = 0; i < item.firstName.size(); ++i) {
        for (int j = i+1; j < item.firstName.size(); ++j) {
            if (item.firstName[i] > item.firstName[j] || (item.firstName[i] == item.firstName[j] && item.lastName[i] > item.lastName[j])) {
                std::swap(item.firstName[i], item.firstName[j]);
                std::swap(item.lastName[i], item.lastName[j]);
                std::swap(item.homePhone[i], item.homePhone[j]);
                std::swap(item.mobilePhone[i], item.mobilePhone[j]);
                std::swap(item.homeAddress[i], item.homeAddress[j]);
                std::swap(item.email[i], item.email[j]);
            }
        }
    }
}

#else
// 使用自定义类存储电话簿项
class PhoneBookItem {
public:
    std::string firstName;
    std::string lastName;
    std::string homePhone;
    std::string mobilePhone;
    std::string homeAddress;
    std::string email;

    bool operator<(const PhoneBookItem& other) const {
        if (firstName == other.firstName) {
            return lastName
        } else {
            return firstName < other.firstName;
        }
    }

    bool operator>(const PhoneBookItem& other) const {
        if (firstName == other.firstName) {
            return lastName > other.lastName;
        } else {
            return firstName > other.firstName;
        }
    }
};

void fillPhoneBookItem(PhoneBookItem& item) {
    std::cout << "Please enter first name: ";
    std::getline(std::cin, item.firstName);
    std::cout << "Please enter last name: ";
    std::getline(std::cin, item.lastName);

    std::cout << "Please enter home phone: ";
    std::getline(std::cin, item.homePhone);

    std::cout << "Please enter mobile phone: ";
    std::getline(std::cin, item.mobilePhone);

    std::cout << "Please enter home address: ";
    std::getline(std::cin, item.homeAddress);

    std::cout << "Please enter email: ";
    std::getline(std::cin, item.email);
}

void printPhoneBookItem(const PhoneBookItem& item) {
    std::cout << "First name: " << item.firstName << std::endl;
    std::cout << "Last name: " << item.lastName << std::endl;
    std::cout << "Home phone: " << item.homePhone << std::endl;
    std::cout << "Mobile phone: " << item.mobilePhone << std::endl;
    std::cout << "Home address: " << item.homeAddress << std::endl;
    std::cout << "Email: " << item.email << std::endl;
}

void sortPhoneBookItem(std::vector<PhoneBookItem>& items) {
    std::sort(items.begin(), items.end(), std::less<PhoneBookItem>());
    std::sort(items.begin(), items.end(), std::greater<PhoneBookItem>());
}

#endif

int main() {
    #ifdef LOTS_OF_VECTORS
    PhoneBookItem item;
    fillPhoneBookItem(item);
    printPhoneBookItem(item);
    sortPhoneBookItem(item);
    #else
    std::vector<PhoneBookItem> items;
    for (int i = 0; i < 3; ++i) {
        PhoneBookItem item;
        fillPhoneBookItem(item);
        items.push_back(item);
    }
    for (const auto& item : items) {
        printPhoneBookItem(item);
    }
    sortPhoneBookItem(items);
    for (const auto& item : items) {
        printPhoneBookItem(item);
    }
    #endif
    return 0;
}
