#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

std::string disk_map(std::string fileContents) {
    std::string disk_space = "";
    int id = 0;
    bool is_file = true;

    for (char ch : fileContents) {
        if (ch == ' ' || ch == '\n') continue;
        
        int blocks = ch - '0';
        
        if (is_file) {
            for(int j = 0; j < blocks; j++) {
                disk_space += std::to_string(id);
            }
            id++;
            is_file = false;
        } else {
            for(int j = 0; j < blocks; j++) {
                disk_space += '#';
            }
            is_file = true;
        }
    }
    return disk_space;
}

std::string ordered_disk(std::string disk_map) {
    std::vector<char> arr(disk_map.begin(), disk_map.end());
    size_t first_free = 0;

    while(first_free < arr.size() && arr[first_free] != '#') {
        first_free++;
    }

    size_t i = arr.size() - 1;
    while(i > 0 && arr[i] == '#') {
        i--;
    }

    while(i > first_free) {
        if(first_free < arr.size() && i < arr.size()) {
            arr[first_free] = arr[i];
            arr[i] = '#';

            i--;
            while(i > first_free && arr[i] == '#') {
                i--;
            }

            first_free++;
            while(first_free < arr.size() && arr[first_free] != '#') {
                first_free++;
            }
        }
    }

    std::string result(arr.begin(), arr.end());
    while (!result.empty() && result.back() == '#') {
        result.pop_back();
    }

    return result;
}

long long check_sum(const std::string& disk_map) {
    long long sum = 0;
    for(size_t i = 0; i < disk_map.length(); i++) {
        if(disk_map[i] != '#') {
            int num = disk_map[i] - '0';
            sum += i * num;
        }
    }
    return sum;
}

int main() {
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return 1;
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();
    std::string fileContents = buffer.str();

    std::string disk = disk_map(fileContents);
    std::string ordered = ordered_disk(disk);
    long long result = check_sum(ordered);

    std::cout << result << std::endl;

    file.close();
    return 0;
}