#include <iostream>
#include <string>
#include <vector>

class MailDeliverySystem {
private:
    std::string defaultDeliveryMethod;
    std::vector<std::string> availableDeliveryMethods;

public:
    MailDeliverySystem(std::string defaultMethod) {
        defaultDeliveryMethod = defaultMethod;
        availableDeliveryMethods.push_back(defaultMethod);
    }

    void setDefaultDeliveryMethod(std::string method) {
        defaultDeliveryMethod = method;
    }

    std::string getDefaultDeliveryMethod() {
        return defaultDeliveryMethod;
    }

    bool isDeliveryMethodAvailable(std::string method) {
        for (std::string availableMethod : availableDeliveryMethods) {
            if (availableMethod == method) {
                return true;
            }
        }
        return false;
    }

    void addDeliveryMethod(std::string method) {
        availableDeliveryMethods.push_back(method);
    }

    void removeDeliveryMethod(std::string method) {
        std::vector<std::string>::iterator it = availableDeliveryMethods.begin();
        while (it != availableDeliveryMethods.end()) {
            if (*it == method) {
                availableDeliveryMethods.erase(it);
                return;
            }
            it++;
        }
    }

    bool operator==(MailDeliverySystem other) {
        return defaultDeliveryMethod == other.getDefaultDeliveryMethod();
    }

    std::string toString() {
        std::string str = "Default delivery method: " + defaultDeliveryMethod + "\n";
        str += "Available delivery methods: ";
        for (std::string method : availableDeliveryMethods) {
            str += method + ", ";
        }
        str.erase(str.end() - 2, str.end());
        return str;
    }

    void sendMail(std::string recipient, std::string subject, std::string body) {
        sendMail(recipient, subject, body, defaultDeliveryMethod);
    }

    void sendMailWithReceipt(std::string recipient, std::string subject, std::string body) {
        std::string methodWithReceipt = defaultDeliveryMethod + " with receipt";
        if (!isDeliveryMethodAvailable(methodWithReceipt)) {
            addDeliveryMethod(methodWithReceipt);
        }
        sendMail(recipient, subject, body, methodWithReceipt);
    }

    void sendMail(std::string recipient, std::string subject, std::string body, std::string deliveryMethod) {
        if (!isDeliveryMethodAvailable(deliveryMethod)) {
            std::cout << "Error: Delivery method not available\n";
            return;
        }
        std::cout << "Sending mail to " << recipient << " using " << deliveryMethod << "...\n";
        // Code for sending mail using specified delivery method
    }
};

int main() {
    MailDeliverySystem deliverySystem("SMTP");
    std::cout << deliverySystem.toString() << "\n";

    deliverySystem.addDeliveryMethod("HTTP");
    std::cout << deliverySystem.toString() << "\n";

    deliverySystem.removeDeliveryMethod("HTTP");
    std::cout << deliverySystem.toString() << "\n";

    std::cout << "Default delivery method: " << deliverySystem.getDefaultDeliveryMethod() << "\n";

    MailDeliverySystem otherDeliverySystem("SMTP");
    if (deliverySystem == otherDeliverySystem) {
        std::cout << "The two delivery systems are equal\n";
    } else {
        std::cout << "The two delivery systems are not equal\n";
    }

    deliverySystem.sendMail("recipient@example.com", "Test email", "This is a test email");
    deliverySystem.sendMailWithReceipt("recipient@example.com", "Test email with receipt", "This is a test email with receipt");
deliverySystem.sendMail("recipient@example.com", "Test email with invalid method", "This is a test email with invalid method", "Invalid method");
return 0;
}
