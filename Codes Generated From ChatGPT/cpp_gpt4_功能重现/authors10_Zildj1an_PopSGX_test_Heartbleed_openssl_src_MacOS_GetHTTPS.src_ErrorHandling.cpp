#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>

#ifdef __EXCEPTIONS_ENABLED__
class ErrorMessageException : public std::runtime_error {
public:
    explicit ErrorMessageException(const std::string& message)
        : std::runtime_error(message) {}
};
#endif

class ErrorHandler {
private:
    std::string errorMessage;

public:
    ErrorHandler() : errorMessage("") {}

    void SetErrorMessage(const std::string& message) {
        errorMessage = message;
    }

    void SetErrorMessageAndCStr(const std::string& message, const char* cstr) {
        errorMessage = message + cstr;
    }

    void SetErrorMessageAndAppendLongInt(const std::string& message, long int value) {
        std::ostringstream oss;
        oss << message << value;
        errorMessage = oss.str();
    }

    std::string GetErrorMessage() const {
        return errorMessage;
    }

    std::string* GetErrorMessageInNewHandle() const {
        return new std::string(errorMessage);
    }

    void GetErrorMessageInExistingHandle(std::string& existingHandle) const {
        existingHandle = errorMessage;
    }

    void AppendCStrToErrorMessage(const char* cstr) {
        errorMessage += cstr;
    }

    void AppendLongIntToErrorMessage(long int value) {
        std::ostringstream oss;
        oss << value;
        errorMessage += oss.str();
    }

#ifdef __EXCEPTIONS_ENABLED__
    void ThrowErrorMessageException() const {
        throw ErrorMessageException(errorMessage);
    }
#endif
};

int main() {
    try {
        ErrorHandler errorHandler;
        errorHandler.SetErrorMessage("Error: ");
        errorHandler.AppendCStrToErrorMessage("Failed to open file with ID ");
        errorHandler.AppendLongIntToErrorMessage(42);
        std::cout << "Error message: " << errorHandler.GetErrorMessage() << std::endl;

        std::string* errorMessageHandle = errorHandler.GetErrorMessageInNewHandle();
        std::cout << "Error message in new handle: " << *errorMessageHandle << std::endl;
        delete errorMessageHandle;

        std::string existingHandle;
        errorHandler.GetErrorMessageInExistingHandle(existingHandle);
        std::cout << "Error message in existing handle: " << existingHandle << std::endl;

#ifdef __EXCEPTIONS_ENABLED__
        errorHandler.ThrowErrorMessageException();
#endif
    } catch (const ErrorMessageException& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }

    return 0;
}
