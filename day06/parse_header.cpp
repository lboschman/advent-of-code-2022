#include <iostream>
#include <fstream>
#include <string>
#include <set>


bool unique_characters(std::string line) {
    std::set<char> unique(line.begin(), line.end());
    return (unique.size() == line.size());
}

int find_header_position(std::string line, int window) {
    int length = line.size();

    for (int i = 0; i < length - window; i++)
    {
        std::string header = line.substr(i, window);
        if (unique_characters(header)) {
            return i + window;
        }
    }

    return -1;
    
}

int main () {
    std::ifstream input("input.txt");
    std::string line;
    getline(input, line);

    std::cout << find_header_position(line, 4) << std::endl;

    std::cout << find_header_position(line, 14) << std::endl;

    return 0;
}