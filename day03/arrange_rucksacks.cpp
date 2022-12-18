#include <string>
#include <iostream>
#include <fstream>
#include <map>


char find_double_item(std::string line) {
    std::string part1, part2;
    int str_len = line.length() / 2;

    part1 = line.substr(0, str_len);
    part2 = line.substr(str_len, str_len);

    // std::cout << part1 << std::endl;
    // std::cout << part2 << std::endl;
    // std::cout << "==============================" << std::endl;

    for (int i = 0; i < str_len; i++)
    {
        char c = part1[i];
        if (part2.contains(c))
        {
            return c;
        }
        
    }

}

int score_char(char letter) {
    std::string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::map<char, int> ctos;

    for (int i = 0; i < letters.length(); i++)
    {
        ctos[letters[i]] = i + 1;
    }
    
    return ctos[letter];
}

int part_1() {
    std::ifstream input("input.txt");

    std::string line;
    int score;

    while (getline(input, line))
    {
        char double_item = find_double_item(line);
        int item_score = score_char(double_item);
        score += item_score;
    }
    
    return score;
}



int main() {
    int score = part_1();

    std::cout << score << std::endl;
    return 0;
}