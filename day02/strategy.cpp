#include <iostream>
#include <fstream>
#include <map>

// meaning:
// opponent:
// - A: rock
// - B: paper
// - C: scissors

// self:
// - X: rock
// - Y: paper
// - Z: scissors

// scoring:
// rock 1, paper 2, scissors 3
// win 6, draw 3, loss 0


int calc_score(char opponent, char you) {

    std::map<char, int> shape_score;
    shape_score['A'] = 0;
    shape_score['B'] = 1;
    shape_score['C'] = 2;
    shape_score['X'] = 0;
    shape_score['Y'] = 1;
    shape_score['Z'] = 2;
    
    // -2 wins
    // -1 loses
    // 0 draws
    // 1 wins
    // 2 loses

    std::map<int, int> score_to_points;
    score_to_points[-2] = 6;
    score_to_points[-1] = 0;
    score_to_points[0] = 3;
    score_to_points[1] = 6;
    score_to_points[2] = 0;

    int score = shape_score[you] + 1;

    int result = score_to_points[shape_score[you] - shape_score[opponent]] ;

    int out = score + result;

    // std::cout << out << std::endl;

    return score + result;
}


int part_1() {
    std::ifstream input("input.txt");

    char opponent, you;
    int score = 0, line = 0;

    while (input >> opponent >> you)
    {
        score += calc_score(opponent, you);
        line += 1;

    }

    std::cout << line << std::endl;
    

    return score;

}



int main() {

    int score_1 = part_1();

    std::cout << score_1 << std::endl;

    
    return 0;
}