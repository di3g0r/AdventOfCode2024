#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

long long concatenate(long long a, long long b) {
    if (b == 0) return a * 10;
    long long b_digits = floor(log10(b)) + 1;
    return a * pow(10, b_digits) + b;
}

long long evaluate_expression(const std::vector<int>& numbers, const std::vector<char>& operators) {
    long long result = numbers[0];
    for (size_t i = 0; i < operators.size(); i++) {
        if (operators[i] == '+') {
            result += numbers[i + 1];
        } else if (operators[i] == '*') {
            result *= numbers[i + 1];
        } else if (operators[i] == '|') {  // Using '|' for concatenation
            result = concatenate(result, numbers[i + 1]);
        }
    }
    return result;
}

bool try_all_combinations(const std::vector<int>& numbers, long long target) {
    int num_operators = numbers.size() - 1;
    int total_combinations = 1 << (2 * num_operators); // 3^n combinations (using 2 bits per operator)
    
    for (int mask = 0; mask < total_combinations; mask++) {
        std::vector<char> operators(num_operators);
        bool valid_combination = true;
        
        // Convert mask to operators
        for (int i = 0; i < num_operators; i++) {
            int op = (mask >> (2 * i)) & 3;  // Get 2 bits for this operator
            if (op == 0) operators[i] = '+';
            else if (op == 1) operators[i] = '*';
            else if (op == 2) operators[i] = '|';
            else {
                valid_combination = false;  // Skip invalid combinations
                break;
            }
        }
        
        if (!valid_combination) continue;
        
        long long result = evaluate_expression(numbers, operators);
        if (result == target) {
            return true;
        }
    }
    return false;
}

std::vector<bool> check_numbers(std::vector<long long> firstNumbers, std::vector<std::vector<int>> correspondingNumbers) {
    std::vector<bool> calibrators;
    
    for(int i = 0; i < firstNumbers.size(); i++) {
        calibrators.push_back(try_all_combinations(correspondingNumbers[i], firstNumbers[i]));
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