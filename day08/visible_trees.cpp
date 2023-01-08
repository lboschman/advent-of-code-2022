#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<int> line_to_vector(std::string line) {
  std::vector<int> output;

  for (int i = 0; i < line.size(); i++)
  {
    output.push_back((line[i] - '0'));
  }
  return output;
}

std::vector<std::vector<int>> read_data() {
  std::ifstream input("input.txt");
  std::string line;

  std::vector<std::vector<int>> data;

  while (getline(input, line)) {
    data.push_back(line_to_vector(line));
  }

  return data;
}

bool visible_in_line(std::vector<int> line, int position) {
  int height = line[position];
  bool visible = true;
  for (int i = 0; i < position; i++)
  {
    if (line[i] >= height) {
      visible = false;
    }
  }

  if (visible) {
    return visible;
  } else {
    visible = true;
  }

  for (int i = position + 1; i < line.size(); i++) {
    if (line[i] >= height) {
      visible = false;
    }
  }

  return visible;
  
}

int check_visible(std::vector<std::vector<int>> data, int x, int y) {
  int height = data[x][y];
  int size0 = data.size();
  int size1 = data[0].size();
  if (x == 0 || x == size0 - 1 || y == 0 || y == size1 - 1) {
    return 1;
  }
  std::vector<int> x_vec = data[x];

  std::vector<int> y_vec = {};
  for (std::vector<int> row : data) {
    y_vec.push_back(row[y]);
  }
  
  if (visible_in_line(x_vec, y) || visible_in_line(y_vec, x)) {

    return 1;
  } else {
    return 0;
  }
}

int line_scenic_score(std::vector<int> line, int pos, bool positive=true) {
  int scenic_score = 1;
  int height = line[pos];
  int size = line.size();

  if (positive) {
    int cursor = pos + 1;
    while (line[cursor] < height && cursor < size) {
      scenic_score++;
      cursor++;
    }

    if (cursor == size) {
      scenic_score--;
    }
  } else {
    int cursor = pos - 1;
    while (line[cursor] < height && cursor >= 0) {
      scenic_score++;
      cursor--;
    }

    if (cursor < 0) {
      scenic_score--;
    }
  }

  // std::cout << "Tree of height " << height << " at pos " << pos << " has scenic score " << scenic_score;
  // if (positive) {
  //   std::cout << " in positive direction" << std::endl;
  // } else {
  //   std::cout << " in negative direction" << std::endl;
  // }

  // std::cout << "Vector used: ";
  // for (int el : line) {
  //   std::cout << el << " ";
  // } 
  // std::cout << std::endl;
  return scenic_score;
}

int calc_scenic_score(std::vector<std::vector<int>> data, int x, int y) {
  int height = data[x][y];
  int size0 = data.size();
  int size1 = data[0].size();

  if (x == 0 || x == size0 - 1 || y == 0 || y == size1 - 1) {
    return 0;
  }

  std::vector<int> x_vec = data[x];

  std::vector<int> y_vec = {};
  for (std::vector<int> row : data) {
    y_vec.push_back(row[y]);
  }
  // std::cout << "Tree at (" << x << ", " << y << ") of height " << height << std::endl;
  int scenic_score = 1;
  scenic_score *= line_scenic_score(x_vec, y, true);
  scenic_score *= line_scenic_score(x_vec, y, false);
  scenic_score *= line_scenic_score(y_vec, x, true);
  scenic_score *= line_scenic_score(y_vec, x, false);

  // std::cout << "==============================" << std::endl;
  return scenic_score;
}

void part1() {
  std::vector<std::vector<int>> data = read_data();

  int size0 = data.size();
  int size1 = data[0].size();

  int visibles = 0;

  for (int i = 0; i < size0; i++)
  {
    for (int j = 0; j < size1; j++)
    {
      visibles += check_visible(data, i, j);
    }
    
  }
  
  std::cout << "Visible trees: " << visibles << std::endl;
}

void part2() {
  std::vector<std::vector<int>> data = read_data();
  std::vector<std::vector<int>> scenic_scores = data;
  
  int max_scenic_score = 0;

  int size0 = data.size();
  int size1 = data[0].size();

  for (int i = 0; i < size0; i++) {
    for (int j = 0; j < size1; j++) {
      int scenic_score = calc_scenic_score(data, i, j);
      scenic_scores[i][j] = scenic_score;
      if (scenic_score > max_scenic_score) {
        max_scenic_score = scenic_score;
      }
    }
  }
  
  std::cout << "Max scenic score: " << max_scenic_score << std::endl;

}


int main() {
  part1();
  part2();
  return 0;
}