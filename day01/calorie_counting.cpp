#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

int main() {

    std::string filename = "input.txt";
    std::ifstream input(filename);

    int max_elf = 0, current_elf = 0, current_cookie = 0;
    std::string str_cur_cookie;
    
    while (!input.eof()) {

        std::getline(input, str_cur_cookie);

        if (str_cur_cookie.length() > 0)
        {
            current_cookie = std::stoi(str_cur_cookie);
            current_elf += current_cookie;
        } else {
            max_elf = std::max(max_elf, current_elf);
            current_elf = 0;
        }
    }

    std::cout << max_elf << std::endl;



    return 0;
}