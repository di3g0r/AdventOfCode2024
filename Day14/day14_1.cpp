#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include <map>

struct Vector2D {
    long long x, y;
    
    Vector2D operator+(const Vector2D& other) const {
        return {x + other.x, y + other.y};
    }
};

struct Robot {
    Vector2D position;
    Vector2D velocity;
};

Robot parseRobot(const std::string& line) {
    std::regex pattern(R"(p=(-?\d+),(-?\d+)\s+v=(-?\d+),(-?\d+))");
    std::smatch matches;
    
    if (std::regex_search(line, matches, pattern)) {
        return {
            {std::stoll(matches[1]), std::stoll(matches[2])},
            {std::stoll(matches[3]), std::stoll(matches[4])}
        };
    }
    
    throw std::runtime_error("Invalid input line: " + line);
}

Vector2D wrap(Vector2D pos, int width, int height) {
    pos.x = ((pos.x % width) + width) % width;
    pos.y = ((pos.y % height) + height) % height;
    return pos;
}

std::vector<int> countQuadrants(const std::vector<Robot>& robots, int width, int height) {
    std::vector<int> counts(4, 0);
    
    int midX = width / 2;
    int midY = height / 2;
    
    for (const auto& robot : robots) {
        if (robot.position.x == midX || robot.position.y == midY) continue;
        
        int quadrant = (robot.position.x > midX ? 1 : 0) + 
                      (robot.position.y > midY ? 2 : 0);
        counts[quadrant]++;
    }
    
    return counts;
}

int main() {
    std::ifstream file("input.txt");
    std::string line;
    std::vector<Robot> robots;
    
    // Read input
    while (std::getline(file, line)) {
        if (!line.empty()) {
            robots.push_back(parseRobot(line));
        }
    }
    
    const int WIDTH = 101;
    const int HEIGHT = 103;
    const int SECONDS = 100;
    
    for (int second = 0; second < SECONDS; second++) {
        for (auto& robot : robots) {
            robot.position = wrap(robot.position + robot.velocity, WIDTH, HEIGHT);
        }
    }
    

    auto quadrantCounts = countQuadrants(robots, WIDTH, HEIGHT);
    
    long long safetyFactor = 1;
    std::cout << "Quadrant counts: ";
    for (int count : quadrantCounts) {
        std::cout << count << " ";
        safetyFactor *= count;
    }
    std::cout << "\nSafety factor: " << safetyFactor << std::endl;
    
    return 0;
}