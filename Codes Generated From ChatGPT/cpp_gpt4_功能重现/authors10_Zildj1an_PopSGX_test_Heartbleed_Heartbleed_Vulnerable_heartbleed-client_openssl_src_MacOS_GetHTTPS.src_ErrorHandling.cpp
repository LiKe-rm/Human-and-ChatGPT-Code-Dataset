#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>

#ifdef __EXCEPTIONS_ENABLED__
class ErrorMessageException : public std::runtime_error {
public:
    explicit ErrorMessageException(const std::string &message)
        : std::runtime_error(message) {}
};
#endif

class ErrorHandlingModule {
private:
    std::string errorMessage;

public:
    void SetErrorMessage(const std::string &message) {
        errorMessage = message;
    }

    void SetErrorMessageAndCStr(const std::string &message, const char *cstr) {
        errorMessage = message;
        errorMessage.append(cstr);
    }

    void SetErrorMessageAndAppendLongInt(const std::string &message, long int value) {
        errorMessage = message;
        errorMessage.append(std::to_string(value));
    }

    const std::string &GetErrorMessage() const {
        return errorMessage;
    }

    void GetErrorMessageInNewHandle(std::string &outputHandle) {
        outputHandle = errorMessage;
    }

    void GetErrorMessageInExistingHandle(std::string &outputHandle) {
        outputHandle.append(errorMessage);
    }

    void AppendCStrToErrorMessage(const char *cstr) {
        errorMessage.append(cstr);
    }

    void AppendLongIntToErrorMessage(long int value) {
        errorMessage.append(std::to_string(value));
    }

#ifdef __EXCEPTIONS_ENABLED__
    void ThrowErrorMessageException() {
        throw ErrorMessageException(errorMessage);
    }
#endif
};

int main() {
    ErrorHandlingModule errorHandlingModule;

    try {
        errorHandlingModule.SetErrorMessage("Error: ");
        errorHandlingModule.AppendCStrToErrorMessage("Invalid input value: ");
        errorHandlingModule.AppendLongIntToErrorMessage(42);

        std::string outputHandle;
        errorHandlingModule.GetErrorMessageInNewHandle(outputHandle);

        std::cout << "Error message: " << outputHandle << std::endl;

#ifdef __EXCEPTIONS_ENABLED__
        errorHandlingModule.ThrowErrorMessageException();
#endif
    }
#ifdef __EXCEPTIONS_ENABLED__
    catch (const ErrorMessageException &e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }
#endif
    catch (...) {
        std::cerr << "Unknown exception caught" << std::endl;
    }

    return 0;
}
