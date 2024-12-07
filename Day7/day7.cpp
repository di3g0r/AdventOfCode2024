#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

// Helper function to evaluate an expression with given operators
long long evaluate_expression(const std::vector<int>& numbers, const std::vector<char>& operators) {
    long long result = numbers[0];
    for (size_t i = 0; i < operators.size(); i++) {
        if (operators[i] == '+') {
            result += numbers[i + 1];
        } else if (operators[i] == '*') {
            result *= numbers[i + 1];
        }
    }
    return result;
}

// Helper function to generate all possible operator combinations
bool try_all_combinations(const std::vector<int>& numbers, long long target) {
    int num_operators = numbers.size() - 1;
    int total_combinations = 1 << num_operators; // 2^n combinations
    
    // Try each possible combination of operators
    for (int mask = 0; mask < total_combinations; mask++) {
        std::vector<char> operators(num_operators);
        for (int i = 0; i < num_operators; i++) {
            operators[i] = (mask & (1 << i)) ? '*' : '+';
        }
        
        if (evaluate_expression(numbers, operators) == target) {
            return true;
        }
    }
    return false;
}

std::vector<bool> check_numbers(std::vector<long long> firstNumbers, std::vector<std::vector<int>> correspondingNumbers) {
    std::vector<bool> calibrators;
    
    for(int i = 0; i < firstNumbers.size(); i++) {
        // Special case for single operator
        if (correspondingNumbers[i].size() == 2) {
            long long sum = correspondingNumbers[i][0] + correspondingNumbers[i][1];
            long long product = (long long)correspondingNumbers[i][0] * correspondingNumbers[i][1];
            calibrators.push_back(sum == firstNumbers[i] || product == firstNumbers[i]);
        }
        // Multiple operators case
        else {
            calibrators.push_back(try_all_combinations(correspondingNumbers[i], firstNumbers[i]));
        }
    }
    
    return calibrators;
}

int main() {
    std::ifstream file("input.txt");
    
    if (!file.is_open()) {
        std::cout << "Error opening file!" << std::endl;
        return 1;
    }
    
    std::vector<long long> firstNumbers;
    std::vector<std::vector<int>> correspondingNumbers;
    
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        
        long long firstNum;
        char colon;
        iss >> firstNum >> colon;
        
        firstNumbers.push_back(firstNum);
        
        std::vector<int> numbers;
        int num;
        
        while (iss >> num) {
            numbers.push_back(num);
        }
        
        correspondingNumbers.push_back(numbers);
    }
    
    file.close();

    std::vector<bool> calibrators = check_numbers(firstNumbers, correspondingNumbers);
    long long sum = 0;
    for(int i = 0; i < calibrators.size(); i++) {
        if(calibrators[i]) {
            sum += firstNumbers[i];
        }
    }

    std::cout << sum << std::endl;
    
    return 0;
}