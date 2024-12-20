#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

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
                prefixes.push_back(prefix);
            }
            isFirstLine = false;
        } else {
            words.push_back(line);
        }
    }

    inputFile.close();

    // std::cout << "Prefixes (" << prefixes.size() << "):" << std::endl;
    // for (const auto& prefix : prefixes) {
    //     std::cout << prefix << " ";
    // }
    // std::cout << std::endl;

    // std::cout << "Words (" << words.size() << "):" << std::endl;
    // for (const auto& word : words) {
    //     std::cout << word << std::endl;
    // }

    return 0;
}
