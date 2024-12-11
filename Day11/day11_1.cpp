#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::string removeLeadingZeros(const std::string& s) {
    if (s == "0" || s.find_first_not_of('0') == std::string::npos) return "0";
    size_t start = s.find_first_not_of('0');
    return s.substr(start);
}

std::string multiplyBy2024(const std::string& num) {
    std::vector<int> result(num.length() + 11, 0);  
    int carry = 0;
    
    for (int i = num.length() - 1; i >= 0; i--) {
        long long product = (num[i] - '0') * 2024LL + carry;
        result[i + 11] = product % 10;
        carry = product / 10;
    }
    
    int idx = 10;
    while (carry > 0) {
        result[idx] = carry % 10;
        carry /= 10;
        idx--;
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

int stones(std::vector<std::string> values, int iterations) {
    for (int iteration = 0; iteration < iterations; iteration++) {
        std::vector<std::string> new_values;
        
        for (const std::string& actual_stone : values) {
            if (actual_stone == "0") {
                new_values.push_back("1");
            } 
            else if (actual_stone.size() % 2 == 0) {
                size_t half = actual_stone.size() / 2;
                std::string first_half = removeLeadingZeros(actual_stone.substr(0, half));
                std::string second_half = removeLeadingZeros(actual_stone.substr(half));
                
                new_values.push_back(first_half);
                new_values.push_back(second_half);
            } 
            else {
                new_values.push_back(multiplyBy2024(actual_stone));
            }
        }
        
        if (iteration < 6) {  
            std::cout << "Iteration " << (iteration + 1) << ": ";
            for (const auto& v : new_values) {
                std::cout << v << " ";
            }
            std::cout << "\nCount: " << new_values.size() << "\n";
        }
        
        values = new_values;
    }
    
    return values.size();
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
    
    std::cout << "Initial values: ";
    for (const auto& v : values) {
        std::cout << v << " ";
    }
    std::cout << "\n";
    
    int result = stones(values, 75);
    std::cout << "Final count after 25 iterations: " << result << "\n";
    
    return 0;
}