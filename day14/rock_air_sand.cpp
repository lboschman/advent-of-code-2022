#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// second coordinate is horizontal coordinate
// first coordinate is vertical coordinate, increasing downwards

struct RockGrid {
  char air = '.';
  char rock = '#';
  char sand = 'o';

  std::vector<std::vector<char>> grid = {{air}};

  void create_single_column() {
    for (int i = 0; i < grid.size(); i++) {
      grid[i].push_back(air);
    }
  }

  void create_columns(int ncols = 1) {
    for (int i = 0; i < ncols; i++) {
      create_single_column();
    }
  }

  void create_single_row() {
    std::vector<char> row((*grid.begin()).size(), air);
    grid.push_back(row);
  }

  void create_rows(int nrows = 1) {
    for (int i = 0; i < nrows; i++) {
      create_single_row();
    }
  }

  void add_rock(int xmin, int xmax, int ymin, int ymax) {
    // make sure that new rock line can fit in the grid

    if (xmin > xmax) {
      int temp = xmin;
      xmin = xmax;
      xmax = temp;
    }

    if (ymin > ymax) {
      int temp = ymin;
      ymin = ymax;
      ymax = temp;
    }

    while (grid[0].size() <= xmax) {
      create_single_column();
    }
    while (grid.size() <= ymax)
      create_single_row();

    if (xmin == xmax)
      add_vertical_rock(xmin, ymin, ymax);
    if (ymin == ymax)
      add_horizontal_rock(xmin, xmax, ymax);
  }

  void add_vertical_rock(int x, int ymin, int ymax) {
    for (int i = ymin; i <= ymax; i++) {
      grid[i][x] = rock;
    }
  }

  void add_horizontal_rock(int xmin, int xmax, int y) {
    for (int i = xmin; i <= xmax; i++) {
      grid[y][i] = rock;
    }
  }
};

RockGrid parse_input(std::string fname) {
  RockGrid canyon;
  std::ifstream input(fname);
  std::string line;

  char comma;
  int i = 0;

  while (getline(input, line)) {
    std::stringstream s(line);
    std::cout << "Parsing line " << i << std::endl;

    int x_start, y_start, x_end, y_end;
    x_end = y_end = 0;
    while (s) {
      if (std::isdigit(s.peek())) {
        x_start = x_end;
        y_start = y_end;
        s >> x_end >> comma >> y_end;
        std::cout << "New Coordinates: " << x_end << ", " << y_end << std::endl;
        if (x_start > 0 && y_start > 0) {
          canyon.add_rock(x_start, x_end, y_start, y_end);
        }
      } else {
        s.ignore(1);
      }
    }

    i++;
  }

  return canyon;
}

int main() {
  RockGrid canyon = parse_input("input_short.txt");
  std::cout << canyon.grid.size() << std::endl;
  std::cout << canyon.grid[0].size() << std::endl;

  return 0;
}