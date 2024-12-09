#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <utility>

using namespace std;

typedef pair<int, int> Point;

bool in_bounds(int x, int y, int n) {
    return 0 <= x && x < n && 0 <= y && y < n;
}

vector<Point> get_antinodes(const Point& a, const Point& b, int n) {
    vector<Point> result;
    int ax = a.first, ay = a.second;
    int bx = b.first, by = b.second;
    
    int dx = bx - ax;
    int dy = by - ay;
    
    // Check points before a
    int i = 0;
    while (true) {
        int x = ax - dx * i;
        int y = ay - dy * i;
        if (!in_bounds(x, y, n)) break;
        result.push_back({x, y});
        i++;
    }
    
    // Check points after b
    i = 0;
    while (true) {
        int x = bx + dx * i;
        int y = by + dy * i;
        if (!in_bounds(x, y, n)) break;
        result.push_back({x, y});
        i++;
    }
    
    return result;
}

int main() {
    ifstream file("input.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }
    
    vector<string> grid;
    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            grid.push_back(line);
        }
    }
    
    int n = grid.size();
    
    // Group antenna locations by frequency
    map<char, vector<Point>> all_locs;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] != '.') {
                all_locs[grid[i][j]].push_back({i, j});
            }
        }
    }
    
    // Find all antinodes
    set<Point> antinodes;
    for (const auto& freq_pair : all_locs) {
        const vector<Point>& locs = freq_pair.second;
        
        // Generate all pairs of antennas with same frequency
        for (size_t i = 0; i < locs.size(); i++) {
            for (size_t j = i + 1; j < locs.size(); j++) {
                // Get and add antinodes for this pair
                vector<Point> new_antinodes = get_antinodes(locs[i], locs[j], n);
                for (const Point& antinode : new_antinodes) {
                    antinodes.insert(antinode);
                }
            }
        }
    }
    
    // Print the visualization
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (antinodes.count({i, j})) {
                cout << "#";
            } else {
                cout << grid[i][j];
            }
        }
        cout << endl;
    }
    
    cout << antinodes.size() << endl;
    
    return 0;
}