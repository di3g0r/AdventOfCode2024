#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility> 
#include <queue>
#include <climits>

struct Node {
    int x, y, dist;
    bool operator>(const Node& other) const { return dist > other.dist; }
};

bool isValid(int x, int y, const std::vector<std::vector<std::string>>& grid) {
    return x >= 0 && x < 71 && y >= 0 && y < 71 && grid[y][x] == ".";
}

int dijkstra(const std::vector<std::vector<std::string>>& grid, int startX, int startY, int endX, int endY) {
    const std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    std::vector<std::vector<int>> dist(71, std::vector<int>(71, INT_MAX));
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;

    pq.push({startX, startY, 0});
    dist[startY][startX] = 0;

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        int x = current.x;
        int y = current.y;

        if (x == endX && y == endY) {
            return current.dist;
        }

        for (const auto& dir : directions) {
            int newX = x + dir.first;
            int newY = y + dir.second;

            if (isValid(newX, newY, grid)) {
                int newDist = current.dist + 1; 
                if (newDist < dist[newY][newX]) {
                    dist[newY][newX] = newDist;
                    pq.push({newX, newY, newDist});
                }
            }
        }
    }

    return -1;
}

int main() {
    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::vector<std::pair<int, int>> coordinates;
    std::string line;

    while (std::getline(inputFile, line)) { 
        std::stringstream ss(line);       
        int x, y;
        char comma;

        ss >> x >> comma >> y;            
        if (ss && comma == ',') {         
            coordinates.emplace_back(x, y); 
        } else {
            std::cerr << "Invalid line format: " << line << std::endl;
        }
    }

    inputFile.close();

    std::vector<std::vector<std::string>> grid(71, std::vector<std::string>(71, "."));

    for (int i = 0; i < coordinates.size(); i++) {
        int x = coordinates[i].first;
        int y = coordinates[i].second;
        if (x >= 0 && x < 71 && y >= 0 && y < 71) {
            grid[y][x] = "#";
        }

        if( i > 1024){
            int path = dijkstra(grid, 0, 0, 70, 70);
            if(path == -1){
                std::cout << x << "," << y;
                break;
            }     
        }
    }

    for (const auto& row : grid) {
        for (const auto& cell : row) {
            std::cout << cell;
        }
        std::cout << "\n";
    }

    //int path = dijkstra(grid, 0, 0, 70, 70);

    //std::cout << path;


    // Access and print the stored coordinates
    // for (const auto& coord : coordinates) {
    //     std::cout << "X: " << coord.first << ", Y: " << coord.second << std::endl;
    // }

    return 0;
}
