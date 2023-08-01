#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <stdexcept>
#include <windows.h>

#include "Scintilla.h"

class ExternalLexerModule;
class LexerLibrary;
class LexerManager;
class LMMinder;

class ExternalLexerModule {
public:
    int GetLanguage() const { return language; }
    ILexer5 *GetLexer() const { return lexer; }

    ExternalLexerModule(int language, ILexer5 *lexer) : language(language), lexer(lexer) {}

private:
    int language;
    ILexer5 *lexer;
};

class LexerLibrary {
public:
    LexerLibrary(const std::string &path) : library(nullptr) {
        library = LoadLibraryA(path.c_str());
        if (!library) {
            throw std::runtime_error("Failed to load lexer library: " + path);
        }

        CreateLexerInstanceFn createLexerInstance = reinterpret_cast<CreateLexerInstanceFn>(
            GetProcAddress(library, "CreateLexerInstance"));
        if (!createLexerInstance) {
            FreeLibrary(library);
            throw std::runtime_error("Failed to find CreateLexerInstance function in library: " + path);
        }

        ILexer5 *lexer = createLexerInstance();
        if (!lexer) {
            FreeLibrary(library);
            throw std::runtime_error("Failed to create lexer instance from library: " + path);
        }

        externalLexerModule = new ExternalLexerModule(lexer->Version(), lexer);
    }

    ~LexerLibrary() {
        if (externalLexerModule) {
            delete externalLexerModule;
        }
        if (library) {
            FreeLibrary(library);
        }
    }

    ExternalLexerModule *GetExternalLexerModule() const {
        return externalLexerModule;
    }

private:
    HMODULE library;
    ExternalLexerModule *externalLexerModule;
};

class LexerManager {
public:
    static LexerManager &GetInstance() {
        static LMMinder minder;
        return minder.instance;
    }

    void LoadLexerLibrary(const std::string &path) {
        LexerLibrary *lexerLibrary = new LexerLibrary(path);
        int language = lexerLibrary->GetExternalLexerModule()->GetLanguage();
        if (libraries.find(language) == libraries.end()) {
            libraries[language] = lexerLibrary;
        } else {
            delete lexerLibrary;
            throw std::runtime_error("Lexer for language already loaded: " + std::to_string(language));
        }
    }

    ILexer5 *GetLexer(int language) {
        auto it = libraries.find(language);
        if (it == libraries.end()) {
            return nullptr;
        }
        return it->second->GetExternalLexerModule()->GetLexer();
    }

private:
    LexerManager() = default;
    ~LexerManager() {
        for (auto &entry : libraries) {
            delete entry.second;
        }
    }

    LexerManager(const LexerManager &) = delete;
    LexerManager &operator=(const LexerManager &) = delete;

    std::map<int, LexerLibrary *> libraries;

    class LMMinder {
    public:
        ~LMMinder() {
            if (instance.libraries.size() > 0) {
                std::cerr << "Warning: Not all lexer libraries were unloaded before shutdown.\n";
            }
        }

        LexerManager instance;
    };
};

int main() {
    try {
        LexerManager &manager = LexerManager::GetInstance();

        // Load a lexer library
        manager.LoadLexerLibrary("path/to/lexer/library.dll");

        // Get a lexer instance for a specific language
        ILexer5 *lexer = manager.GetLexer(1); // Replace 1 with the appropriate language identifier
        if (!lexer) {
            std::cerr << "Error: Failed to get lexer for language.\n";
            return 1;
        }

        // Use the lexer instance as needed
        // ...

        // No need to delete the lexer instance as it is managed by LexerManager
    } catch (const std::runtime_error &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

