#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <cmath>

struct ClawMachine {
    long long buttonA_x, buttonA_y;
    long long buttonB_x, buttonB_y;
    long long prize_x, prize_y;
};

bool isInteger(double x) {
    return std::abs(x - std::round(x)) < 1e-10;
}

bool solveMachine(const ClawMachine& m, long long& tokens) {
    // Add 10 trillion to prize coordinates
    long long px = m.prize_x + 10000000000000LL;
    long long py = m.prize_y + 10000000000000LL;
    
    double den = (m.buttonA_x * m.buttonB_y - m.buttonA_y * m.buttonB_x);
    if (den == 0) return false;  
    
    double a_presses = (px * m.buttonB_y - py * m.buttonB_x) / (double)den;
    
    if (!isInteger(a_presses) || a_presses < 0) return false;
    
    double b_presses = (px - a_presses * m.buttonA_x) / m.buttonB_x;
    
    if (!isInteger(b_presses) || b_presses < 0) return false;
    
    if (std::abs(a_presses * m.buttonA_y + b_presses * m.buttonB_y - py) > 1e-10) 
        return false;
    
    tokens = 3 * (long long)a_presses + (long long)b_presses;
    return true;
}

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
            long long x = std::stoll(matches[1]);
            long long y = std::stoll(matches[2]);
            
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

int main() {
    auto machines = readInput("input.txt");
    long long totalTokens = 0;
    int solvableMachines = 0;
    
    for (size_t i = 0; i < machines.size(); i++) {
        long long tokens;
        bool solvable = solveMachine(machines[i], tokens);
        
        if (solvable) {
            //std::cout << "Machine " << i+1 << " is solvable with " << tokens << " tokens\n";
            totalTokens += tokens;
            solvableMachines++;
        }
    }
    
    std::cout << "Total tokens needed: " << totalTokens << std::endl;
    
    return 0;
}