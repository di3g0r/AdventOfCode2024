#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include <climits>
#include <string>

using namespace std;

struct Point {
    int row, col;
    Point(int r = 0, int c = 0) : row(r), col(c) {}
    bool operator<(const Point& other) const {
        return tie(row, col) < tie(other.row, other.col);
    }
    bool operator==(const Point& other) const {
        return row == other.row && col == other.col;
    }
};

class Solver {
private:
    vector<string> grid;
    int rows, cols;
    Point start, end;
    vector<pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    bool isValid(int row, int col) const {
        return row >= 0 && row < rows && col >= 0 && col < cols;
    }

    bool isWalkable(int row, int col) const {
        return isValid(row, col) && grid[row][col] != '#';
    }

public:
    Solver(const vector<string>& input) : grid(input) {
        rows = grid.size();
        cols = grid[0].size();
        
        // Find start and end positions
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == 'S') start = Point(i, j);
                if (grid[i][j] == 'E') end = Point(i, j);
            }
        }
    }

    vector<vector<int>> calculateDistancesToEnd() {
        vector<vector<int>> distances(rows, vector<int>(cols, INT_MAX));
        queue<pair<Point, int>> q;
        
        q.push({end, 0});
        distances[end.row][end.col] = 0;
        
        while (!q.empty()) {
            auto [current, dist] = q.front();
            q.pop();
            
            for (auto [dr, dc] : dirs) {
                int newRow = current.row + dr;
                int newCol = current.col + dc;
                
                if (isWalkable(newRow, newCol) && distances[newRow][newCol] == INT_MAX) {
                    distances[newRow][newCol] = dist + 1;
                    q.push({Point(newRow, newCol), dist + 1});
                }
            }
        }
        
        return distances;
    }

    vector<int> findShortcuts() {
        vector<vector<int>> distToEnd = calculateDistancesToEnd();
        int baseDistance = distToEnd[start.row][start.col];
        vector<int> savings;
        
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                if (!isWalkable(row, col) || distToEnd[row][col] == INT_MAX) continue;
                int startDist = distToEnd[row][col];
                
                for (auto [dr1, dc1] : dirs) {
                    int r1 = row + dr1;
                    int c1 = col + dc1;
                    if (!isValid(r1, c1)) continue;
                    
                    for (auto [dr2, dc2] : dirs) {
                        int r2 = r1 + dr2;
                        int c2 = c1 + dc2;
                        if (!isValid(r2, c2) || !isWalkable(r2, c2)) continue;
                        
                        int endDist = distToEnd[r2][c2];
                        if (endDist == INT_MAX) continue;
                        
                        int distToStart = baseDistance - startDist;
                        int totalDist = distToStart + 2 + endDist; 
                        
                        if (totalDist < baseDistance) {
                            savings.push_back(baseDistance - totalDist);
                        }
                    }
                }
            }
        }
        
        return savings;
    }
};

int main() {
    // Read input
    vector<string> grid;
    string line;
    while (getline(cin, line)) {
        if (!line.empty()) {
            grid.push_back(line);
        }
    }
    
    Solver solver(grid);
    auto savings = solver.findShortcuts();
    
    // Count shortcuts that save >= 100 steps
    int count = 0;
    for (int saving : savings) {
        if (saving >= 100) count++;
    }
    
    cout << "Number of cheats saving >= 100 picoseconds: " << count << endl;
    
    return 0;
}