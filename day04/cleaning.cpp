#include <iostream>
#include <fstream>
#include <string>

struct cleaning_range
{
    int lower;
    int upper;
};

int fully_contained_ranges(cleaning_range range1, cleaning_range range2){
    if ((range1.lower <= range2.lower && range1.upper >= range2.upper) || 
        (range1.lower >= range2.lower && range1.upper <= range2.upper)
    ) {
        return 1;
    } else {
        return 0;
    }
}

cleaning_range make_range(std::string line) {
    char sep = '-';
    std::size_t pos = line.find(sep);

    cleaning_range range;

    range.lower = std::stoi(line.substr(0, pos));
    range.upper = std::stoi(line.substr(pos+1));

    return range;
}

int parse_line(std::string line) {
    std::string line1, line2;
    cleaning_range range1, range2;

    std::size_t pos = line.find(',');
    line1 = line.substr(0, pos);
    line2 = line.substr(pos+1);

    range1 = make_range(line1);
    range2 = make_range(line2);

    return fully_contained_ranges(range1, range2);

}



int part_1() {
    std::ifstream input("input.txt");
    std::string line;
    int score;

    while (getline(input,line))
    {
        score += parse_line(line);
    }
    
    return score;

}


int main() {
    int score_1 = part_1();

    std::cout << score_1 << std::endl;

    return 0;
}