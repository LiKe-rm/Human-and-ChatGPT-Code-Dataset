#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <Windows.h>
#include <DbgHelp.h>

using namespace std;

// Data structure to hold information about a tracked string
struct TrackedString {
    string text;
    vector<int> pattern;
    int next_byte_index;
    DWORD address;
};

// Global variables to hold information about the tracked strings and search state
vector<TrackedString> tracked_strings;
bool searching = false;
ofstream log_file;

// Utility function to convert a string to a vector of integer pattern bytes
vector<int> string_to_pattern(const string& text) {
    vector<int> pattern;
    for (int i = 0; i < text.length(); i++) {
        if (text[i] == '?') {
            pattern.push_back(-1);
        }
        else {
            pattern.push_back(static_cast<int>(text[i]));
        }
    }
    return pattern;
}

// Callback function to track reads and writes to memory
void mem_callback(ULONG_PTR address, SIZE_T size, bool is_write) {
    if (searching) {
        for (int i = 0; i < tracked_strings.size(); i++) {
            TrackedString& tracked_string = tracked_strings[i];
            int pattern_byte = tracked_string.pattern[tracked_string.next_byte_index];
            if (pattern_byte == -1 || pattern_byte == static_cast<int>(*(reinterpret_cast<unsigned char*>(address)))) {
                tracked_string.next_byte_index++;
                if (tracked_string.next_byte_index == tracked_string.pattern.size()) {
                    // Match found, log the result and reset the tracked string
                    tracked_string.next_byte_index = 0;
                    tracked_string.address = address - tracked_string.pattern.size() + 1;
                    log_file << tracked_string.text << " found at address " << tracked_string.address << endl;

                    // Log the call stack
                    void* stack[100];
                    HANDLE process = GetCurrentProcess();
                    SymSetOptions(SYMOPT_LOAD_LINES);
                    SymInitialize(process, NULL, TRUE);
                    WORD numberOfFrames = CaptureStackBackTrace(0, 100, stack, NULL);
                    SYMBOL_INFO* symbol = (SYMBOL_INFO*)malloc(sizeof(SYMBOL_INFO) + 256 * sizeof(char));
                    symbol->MaxNameLen = 255;
                    symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
                    for (int i = 0; i < numberOfFrames; i++) {
                        SymFromAddr(process, (DWORD64)(stack[i]), 0, symbol);
                        IMAGEHLP_LINE64 line = { sizeof(IMAGEHLP_LINE64) };
                        DWORD displacement;
                        if (SymGetLineFromAddr64(process, (DWORD64)(stack[i]), &displacement, &line)) {
                            log_file << "\t" << symbol->Name << " at " << line.FileName << ":" << line.LineNumber << endl;
                        }
                        else {
                            log_file << "\t" << symbol->Name << " at unknown location" << endl;
                        }
                    }
                    free(symbol);
                }
            }
            else {
                tracked_string.next_byte_index = 0;
            }
        }
    }
}

// Utility function to start the search
void start_search() {
    searching = true;
    log_file.open("search_results.txt");

    // Read in the tracked strings from a file
    ifstream string_file("strings.txt");
    string line;
    while (getline(string_file, line)) {
        TrackedString tracked_string;
       
    tracked_string.text = line;
    tracked_string.pattern = string_to_pattern(line);
    tracked_strings.push_back(tracked_string);
}

// Set up the memory callback function
SetMemCallback(mem_callback);

// Log the start of the search
log_file << "Starting search..." << endl;
}

// Utility function to stop the search and log the results
void stop_search() {
searching = false;
log_file << "Search complete." << endl;
log_file.close();
}

int main() {
start_search();// Main program loop
while (true) {
    // Do some other work here, or sleep to avoid using too much CPU
    Sleep(1000);

    // Check for a key press to stop the search
    if (GetAsyncKeyState(VK_ESCAPE)) {
        stop_search();
        break;
    }
}

return 0;
}