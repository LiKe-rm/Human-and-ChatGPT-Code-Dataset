#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <cstdlib>
#include <algorithm>

// Function to split a string by a delimiter
std::vector<std::string> splitStringByDelimiter(const std::string &str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    for (const char &c : str) {
        if (c == delimiter) {
            tokens.push_back(token);
            token.clear();
        } else {
            token += c;
        }
    }
    tokens.push_back(token);
    return tokens;
}

// Function to populate decks
void populateDecks(const std::string &filePath, std::map<std::string, std::string> &deck, const std::vector<int> &acceptedSets) {
    std::ifstream file(filePath);
    std::string line;

    if (!file) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        exit(1);
    }

    while (std::getline(file, line)) {
        std::vector<std::string> tokens = splitStringByDelimiter(line, '\t');
        if (tokens.size() == 3) {
            int setNumber = std::stoi(tokens[0]);
            if (acceptedSets.empty() || std::find(acceptedSets.begin(), acceptedSets.end(), setNumber) != acceptedSets.end()) {
                deck[tokens[1]] = tokens[2];
            }
        }
    }
    file.close();
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <red_cards_file> <green_cards_file>" << std::endl;
        return 1;
    }

    std::srand(std::time(nullptr));
    std::string redCardsPath = argv[1];
    std::string greenCardsPath = argv[2];

    std::map<std::string, std::string> redDeck;
    std::map<std::string, std::string> greenDeck;

    std::vector<int> acceptedSets; // Fill this vector with set numbers if needed, otherwise leave it empty to include all sets
    populateDecks(redCardsPath, redDeck, acceptedSets);
    populateDecks(greenCardsPath, greenDeck, acceptedSets);

    if (redDeck.empty() || greenDeck.empty()) {
        std::cerr << "Error: One or both decks are empty. Please check the input files." << std::endl;
        return 1;
    }

    auto redCard = redDeck.begin();
    std::advance(redCard, std::rand() % redDeck.size());
    auto greenCard = greenDeck.begin();
    std::advance(greenCard, std::rand() % greenDeck.size());

    std::cout << "Red Card: " << redCard->first << " (" << redCard->second << ")" << std::endl;
    std::cout << "Green Card: " << greenCard->first << " (" << greenCard->second << ")" << std::endl;

    return 0;
}
