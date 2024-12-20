#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

long long countWaysHelper(const std::string& word, const std::vector<std::string>& prefixes, std::unordered_map<std::string, long long>& memo) {
    if (word.empty()) {
        return 1; 
    }

    if (memo.find(word) != memo.end()) {
        return memo[word]; 
    }

    long long ways = 0; 

    for (const std::string& prefix : prefixes) {
        if (word.substr(0, prefix.size()) == prefix) { 
            std::string rest = word.substr(prefix.size());
            ways += countWaysHelper(rest, prefixes, memo); 
        }
    }

    memo[word] = ways; 
    return ways;
}

long long countTotalWays(const std::vector<std::string>& words, const std::vector<std::string>& prefixes) {
    long long totalWays = 0;
    std::unordered_map<std::string, long long> memo;

    for (const std::string& word : words) {
        totalWays += countWaysHelper(word, prefixes, memo); 
    }

    return totalWays;
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

    // Verificar prefijos y palabras
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

    // Calcular el número total de formas de componer palabras
    long long result = countTotalWays(words, prefixes);

    std::cout << "Total ways to compose words: " << result << std::endl;

    return 0;
}
