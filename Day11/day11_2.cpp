#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>

struct CacheKey {
    std::string number;
    int remainingIterations;
    
    bool operator==(const CacheKey& other) const {
        return number == other.number && remainingIterations == other.remainingIterations;
    }
};

struct CacheKeyHash {
    std::size_t operator()(const CacheKey& k) const {
        return std::hash<std::string>()(k.number) ^ std::hash<int>()(k.remainingIterations);
    }
};

std::unordered_map<CacheKey, long long, CacheKeyHash> cache;

std::string removeLeadingZeros(const std::string& s) {
    if (s.empty() || (s.size() == 1 && s[0] == '0')) return "0";
    size_t start = s.find_first_not_of('0');
    if (start == std::string::npos) return "0";
    return s.substr(start);
}

std::string multiplyBy2024(const std::string& num) {
    if (num == "0") return "0";
    
    std::vector<int> result(num.length() + 11, 0);
    int carry = 0;
    
    for (int i = num.length() - 1; i >= 0; i--) {
        long long product = (num[i] - '0') * 2024LL + carry;
        result[i + 11] = product % 10;
        carry = product / 10;
    }
    
    int idx = 10;
    while (carry > 0) {
        result[idx--] = carry % 10;
        carry /= 10;
    }
    
    std::string final;
    bool leadingZero = true;
    for (int digit : result) {
        if (digit != 0 || !leadingZero) {
            leadingZero = false;
            final += std::to_string(digit);
        }
    }
    
    return final.empty() ? "0" : final;
}

long long processStoneRecursive(const std::string& stone, int iterations) {
    if (iterations == 0) return 1;
    
    CacheKey key{stone, iterations};
    if (cache.find(key) != cache.end()) {
        return cache[key];
    }
    
    long long result;
    
    if (stone == "0") {
        result = processStoneRecursive("1", iterations - 1);
    }
    else if (stone.size() % 2 == 0) {
        size_t half = stone.size() / 2;
        std::string first = removeLeadingZeros(stone.substr(0, half));
        std::string second = removeLeadingZeros(stone.substr(half));
        result = processStoneRecursive(first, iterations - 1) + 
                processStoneRecursive(second, iterations - 1);
    }
    else {
        result = processStoneRecursive(multiplyBy2024(stone), iterations - 1);
    }
    
    cache[key] = result;
    return result;
}

long long processStones(const std::vector<std::string>& initialStones, int iterations) {
    long long totalStones = 0;
    cache.clear();  
    
    for (const auto& stone : initialStones) {
        totalStones += processStoneRecursive(stone, iterations);
    }
    
    return totalStones;
}

int main() {
    std::string filename = "input.txt";
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return 1;
    }
    
    std::vector<std::string> values;
    std::string value;
    while (file >> value) {
        values.push_back(value);
    }
    
    std::cout << "Processing 75 iterations...\n";
    long long result = processStones(values, 75);
    std::cout << "Final count after 75 iterations: " << result << "\n";
    
    return 0;
}