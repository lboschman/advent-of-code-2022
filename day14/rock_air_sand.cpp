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
  int dropped_sand = 0;

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

  int drop_block_sand(int origin_x, int origin_y) {
    grid[origin_y][origin_x] = sand;
    int response = move_block_sand(origin_x, origin_y);
    dropped_sand += (1+response);
    return response;
  }

  int move_block_sand(int x, int y) {
    // return values:
    // 1: block needs to move
    // 0: block cannot move, terminate
    // -1: block has fallen off the grid, terminate

    // overflow condition
    if (y==grid.size() - 1) {
      return -1;
    }

    // drop straight down
    if (grid[y+1][x]==air) {
      grid[y][x] = air;
      grid[y+1][x] = sand;
      return move_block_sand(x, y+1);
    // if not straight down, move down-left (problem specification)
    } else if (grid[y+1][x-1]==air) {
      grid[y][x] = air;
      grid[y+1][x-1] = sand;
      return move_block_sand(x-1, y+1);
    // if not down-left, move down-right (problem specification)
    } else if (grid[y+1][x+1]==air) {
      grid[y][x] = air;
      grid[y+1][x+1] = sand;
      return move_block_sand(x+1, y+1);
    } else {
      return 0;
    }
  }

  void drop_all_sand(int origin_x, int origin_y) {
    int overflow = 0;
    while (overflow==0) {
      overflow = drop_block_sand(origin_x, origin_y);
    }
  }

  void print_grid() {
    for (auto line : grid) {
      for (char c : line) {
        std::cout << c;
      }
      std::cout << std::endl;
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
    // std::cout << "Parsing line " << i << std::endl;

    int x_start, y_start, x_end, y_end;
    x_end = y_end = 0;
    while (s) {
      if (std::isdigit(s.peek())) {
        x_start = x_end;
        y_start = y_end;
        s >> x_end >> comma >> y_end;
        // std::cout << "New Coordinates: " << x_end << ", " << y_end << std::endl;
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
  RockGrid canyon = parse_input("input.txt");
  canyon.drop_all_sand(500, 0);

  std::cout << "Dropped blocks of sand: " << canyon.dropped_sand << std::endl;

}