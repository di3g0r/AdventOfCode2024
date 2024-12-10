#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib> // For std::atoi


std::string disk_map(std::string fileContents) {
    std::string disk_space = "";
    int num = 0;
    std::string current_number = "";

    for (size_t i = 0; i < fileContents.size(); ++i) {
        if (fileContents[i] == '\n' || fileContents[i] == ' ') continue;
        
        // Print consecutive pairs to see what we're reading
        if (i % 2 == 0) {
            std::cout << fileContents[i] << fileContents[i+1] << " "; 
        }
        
        if (i % 2 == 0) { // File size
            int file_blocks = fileContents[i] - '0';
            for(int j = 0; j < file_blocks; j++){
                disk_space += std::to_string(num);
            }
            num++;
        } else { // Free space
            int free_blocks = fileContents[i] - '0';
            for(int j = 0; j < free_blocks; j++){
                disk_space += '#';
            }
        }
    }
    return disk_space;
}

std::string ordered_disk(std::string disk_map) {
    int first_free = 0;
    // Find first free space
    while (first_free < disk_map.length() && disk_map[first_free] != '#') {
        first_free++;
    }
    
    int i = disk_map.length() - 1;
    // Find last file
    while (i >= 0 && disk_map[i] == '#') {
        i--;
    }
    
    while (i > first_free) {
        disk_map[first_free] = disk_map[i];
        disk_map[i] = '#';
        
        // Find next file from end
        while (i >= 0 && disk_map[i] == '#') {
            i--;
        }
        // Find next free space from start
        while (first_free < disk_map.length() && disk_map[first_free] != '#') {
            first_free++;
        }
    }
    
    // Remove trailing #s
    while (!disk_map.empty() && disk_map.back() == '#') {
        disk_map.pop_back();
    }
    
    return disk_map;
}

int check_sum(std::string disk_map){
    int sum = 0;
    for(int i=0; i < disk_map.length(); i++){
        int num = disk_map[i] - '0';
        sum += i * num;
    }

    std::cout << sum << "\n";

    return sum;
}

int main() {
    std::ifstream file("input.txt"); // Open the file
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return 1;
    }

    std::ostringstream buffer;
    buffer << file.rdbuf(); 
    std::string fileContents = buffer.str(); 

    //std::cout << "File contents:\n" << fileContents << std::endl;
    std::string disk = " ";

    disk = disk_map(fileContents);

    std::string order = " ";

    order = ordered_disk(disk);

    check_sum(order);

    file.close(); // Close the file
    return 0;
}

// 0099811188827773336446555566
// 009981118882777333644655556666