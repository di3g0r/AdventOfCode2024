#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm> 

bool composableHelper(const std::string& word, const std::vector<std::string>& prefixes, std::unordered_map<std::string, bool>& memo) {
    if (word.empty()) {
        return true; 
    }

    if (memo.find(word) != memo.end()) {
        return memo[word]; 
    }


    for (const std::string& prefix : prefixes) {
        if (word.substr(0, prefix.size()) == prefix) {
            std::string rest = word.substr(prefix.size()); 
            if (composableHelper(rest, prefixes, memo)) {
                memo[word] = true;
                return true;
            }
        }
    }

    memo[word] = false; 
    return false;
}

int countComposableWords(const std::vector<std::string>& words, const std::vector<std::string>& prefixes) {
    int count = 0;
    std::unordered_map<std::string, bool> memo;

    for (const std::string& word : words) {
        if (composableHelper(word, prefixes, memo)) {
            count++;
        }
    }

    return count;
}

int main() {
    std::vector<std::string> prefixes;
    std::vector<std::string> words;

    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open file." << std::endl;
        return 1;
    }

    std::string line;
    bool isFirstLine = true;

    while (std::getline(inputFile, line)) {
        if (isFirstLine) {
            std::stringstream ss(line);
            std::string prefix;
            while (std::getline(ss, prefix, ',')) {
                // Eliminar espacios en blanco antes o después del prefijo
                prefix.erase(remove_if(prefix.begin(), prefix.end(), isspace), prefix.end());
                prefixes.push_back(prefix);
            }
            isFirstLine = false;
        } else {
            if (!line.empty()) {
                words.push_back(line);
            }
        }
    }

    inputFile.close();

    // std::cout << "Prefixes (" << prefixes.size() << "): ";
    // for (const auto& prefix : prefixes) {
    //     std::cout << prefix << " ";
    // }
    // std::cout << std::endl;

    // std::cout << "Words (" << words.size() << "): ";
    // for (const auto& word : words) {
    //     std::cout << word << " ";
    // }
    // std::cout << std::endl;


    int result = countComposableWords(words, prefixes);

    std::cout << "Number of composable words: " << result << std::endl;

    return 0;
}
