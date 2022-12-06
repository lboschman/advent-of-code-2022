#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

int part_1() {
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

    return max_elf;
}

int part_2() {
    std::string filename = "input.txt";
    std::ifstream input(filename);

    int current_elf = 0, current_cookie = 0;
    std::string str_cur_cookie;

    std::vector<int> all_elves;

    while (!input.eof())
    {
        std::getline(input, str_cur_cookie);
        if (str_cur_cookie.length() > 0) {
            current_cookie = std::stoi(str_cur_cookie);
            current_elf += current_cookie;
        } else {
            all_elves.push_back(current_elf);
            current_elf = 0;
        }
        
    }

    std::sort(all_elves.begin(), all_elves.end());
    std::reverse(all_elves.begin(), all_elves.end());
    
    int top_3 = all_elves[0] + all_elves[1] + all_elves[2];

    return top_3;
    
}


int main() {
    int max_elf = part_1();

    int max_3 = part_2();

    std::cout << max_elf << std::endl;
    std::cout << max_3 << std::endl;

    return 0;
}
