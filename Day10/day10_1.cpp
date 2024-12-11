#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
typedef pair<int, int> Point;

// int check_paths(vector<string> grid, Point zero, vector<Point>& nines) {
//     vector<Point> visited_nines = nines;
//     Point starting_point = zero;
//     Point actual_point = starting_point;
//     int actual = 0;
//     //cout << "Par de ceros: (" << p1.first << ", " << p1.second << ")\n";
//     while(grid.size() > actual_point.first > -1 && grid[0].size() > actual_point.second > -1){

//     }
    

//     return 0; 
// }

vector<Point> find_zeros(const vector<string>& grid) {
    vector<Point> zeros;

    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].length(); j++) {
            if (grid[i][j] == '0') {
                zeros.push_back({i, j});
            }
        }
    }

    return zeros;
}

vector<Point> find_nines(const vector<string>& grid) {
    vector<Point> nines;

    for (int i = 0; i < grid.size(); i++) { 
        for (int j = 0; j < grid[i].length(); j++) {
            if (grid[i][j] == '9') {
                nines.push_back({i, j});
            }
        }
    }

    return nines;
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

    cout << "Grid:" << endl;
    for (const auto& row : grid) {
        cout << row << endl;
    }
    cout << endl;

    vector<Point> zeros = find_zeros(grid);
    vector<Point> nines = find_nines(grid);

    //check_paths(grid, zeros[0], nines);

    return 0;
}
