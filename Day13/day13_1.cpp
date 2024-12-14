#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <limits>

struct ClawMachine {
    int buttonA_x, buttonA_y;  // Button A movements
    int buttonB_x, buttonB_y;  // Button B movements
    int prize_x, prize_y;      // Prize location
};

std::vector<ClawMachine> readInput(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    std::vector<ClawMachine> machines;
    ClawMachine current;
    
    std::regex coord_pattern(R"(X[\+=](\d+),\s*Y[\+=](\d+))");
    int lineInSet = 0;
    
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        std::smatch matches;
        if (std::regex_search(line, matches, coord_pattern)) {
            int x = std::stoi(matches[1]);
            int y = std::stoi(matches[2]);
            
            switch (lineInSet) {
                case 0:  // Button A
                    current.buttonA_x = x;
                    current.buttonA_y = y;
                    break;
                case 1:  // Button B
                    current.buttonB_x = x;
                    current.buttonB_y = y;
                    break;
                case 2:  // Prize
                    current.prize_x = x;
                    current.prize_y = y;
                    machines.push_back(current);
                    break;
            }
            
            lineInSet = (lineInSet + 1) % 3;
        }
    }
    
    return machines;
}

// Function to check if a solution exists and find minimum tokens
int solveMachine(const ClawMachine& machine) {
    int minTokens = std::numeric_limits<int>::max();
    
    for (int a = 0; a <= 100; a++) {
        for (int b = 0; b <= 100; b++) {
            long long x = (long long)a * machine.buttonA_x + (long long)b * machine.buttonB_x;
            long long y = (long long)a * machine.buttonA_y + (long long)b * machine.buttonB_y;
            
            if (x == machine.prize_x && y == machine.prize_y) {
                int tokens = 3 * a + b;
                minTokens = std::min(minTokens, tokens);
            }
        }
    }
    
    return (minTokens == std::numeric_limits<int>::max()) ? -1 : minTokens;
}

int main() {
    auto machines = readInput("input.txt");
    
    int totalTokens = 0;
    int solvableMachines = 0;
    
    std::cout << "Found " << machines.size() << " machines\n\n";
    
    for (size_t i = 0; i < machines.size(); i++) {
        const auto& m = machines[i];
        std::cout << "Machine " << i+1 << ":\n";
        std::cout << "Button A: (" << m.buttonA_x << "," << m.buttonA_y << ")\n";
        std::cout << "Button B: (" << m.buttonB_x << "," << m.buttonB_y << ")\n";
        std::cout << "Prize: (" << m.prize_x << "," << m.prize_y << ")\n";
        
        int tokens = solveMachine(machines[i]);
        if (tokens != -1) {
            std::cout << "Can be solved with " << tokens << " tokens\n";
            totalTokens += tokens;
            solvableMachines++;
        } else {
            std::cout << "Cannot be solved\n";
        }
        std::cout << "\n";
    }
    
    std::cout << "Total solvable machines: " << solvableMachines << std::endl;
    std::cout << "Total tokens needed: " << totalTokens << std::endl;
    
    return 0;
}