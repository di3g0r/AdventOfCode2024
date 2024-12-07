#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

std::vector<bool> check_numbers(std::vector<long long> firstNumbers, std::vector<std::vector<int>> correspondingNumbers){
    std::vector<bool> calibrators;

    for(int i=0; i < firstNumbers.size(); i++){
        int nums = correspondingNumbers[i].size();
        bool found = false;
        
        for(int mask = 0; mask < (1 << (nums-1)) && !found; mask++) {
            long long testResult = correspondingNumbers[i][0];
            
            // Evaluate left to right using the current combination
            for(int j = 0; j < nums-1; j++) {
                if(mask & (1 << j)) {
                    testResult *= correspondingNumbers[i][j+1];
                } else {
                    testResult += correspondingNumbers[i][j+1];
                }
            }
            
            if(testResult == firstNumbers[i]) {
                found = true;
            }
        }
        
        calibrators.push_back(found);
        
    }

    return calibrators;
}

int main() {
    std::ifstream file("input.txt");
    
    if (!file.is_open()) {
        std::cout << "Error opening file!" << std::endl;
        return 1;
    }
    
    // Vector to store the first numbers (190, 3267, etc.)
    std::vector<long long> firstNumbers;
    // Vector of vectors to store the corresponding numbers for each line
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

    std::vector<bool> calibrators;
    calibrators = check_numbers(firstNumbers, correspondingNumbers);
    long long sum = 0;
    for(int i = 0; i < calibrators.size(); i++){
        if(calibrators[i] == true){
            sum += firstNumbers[i];
            std::cout << firstNumbers[i] << "\n";
        }
    }

    std::cout << sum;
    
    // Print results to verify
    // std::cout << "First numbers: ";
    // for (int num : firstNumbers) {
    //     std::cout << num << " ";
    // }
    // std::cout << "\n\n";
    
    // std::cout << "Corresponding numbers for each line:\n";
    // for (size_t i = 0; i < correspondingNumbers.size(); i++) {
    //     std::cout << "Line " << i + 1 << ": ";
    //     for (int num : correspondingNumbers[i]) {
    //         std::cout << num << " ";
    //     }
    //     std::cout << "\n";
    // }
    
    return 0;
}