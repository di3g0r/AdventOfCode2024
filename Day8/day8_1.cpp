#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <utility>

using namespace std;

// Equivalent to Python's tuple for coordinates
typedef pair<int, int> Point;

// Check if coordinates are within bounds
bool in_bounds(int x, int y, int n) {
    return 0 <= x && x < n && 0 <= y && y < n;
}

// Get antinodes for a pair of antennas
vector<Point> get_antinodes(const Point& a, const Point& b, int n) {
    vector<Point> result;
    int ax = a.first, ay = a.second;
    int bx = b.first, by = b.second;
    
    // Calculate potential antinode positions
    int cx = ax - (bx - ax);
    int cy = ay - (by - ay);
    int dx = bx + (bx - ax);
    int dy = by + (by - ay);
    
    if (in_bounds(cx, cy, n)) {
        result.push_back({cx, cy});
    }
    if (in_bounds(dx, dy, n)) {
        result.push_back({dx, dy});
    }
    
    return result;
}

int main() {
    // Read input file
    ifstream file("input.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }
    
    vector<string> grid;
    string line;
    while (getline(file, line)) {
        if (!line.empty()) { // Skip empty lines
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
    
    cout << antinodes.size() << endl;
    
    return 0;
}