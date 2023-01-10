#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>


class RopeEnd {
  public:
    int x;
    int y;
    RopeEnd* follower = nullptr;
    bool log_motion;

    static std::vector<std::string> visited_positions;

    RopeEnd() {
      x = 0;
      y = 0;
      log_motion = false;
    }

    RopeEnd(int px, int py, bool p_log_motion=false) {
      x = px;
      y = py;
      log_motion = p_log_motion;
    }

    void move(char direction, int steps) {
      for (int i = 0; i < steps; i++)
      {
        this->move_single_step(direction);
        if (follower) {
          follower->follow(this->x, this->y);
        }
      }
      
    }

    void move_single_step(char direction) {
      switch (direction)
      {
      case 'U':
        y++;
        break;
      case 'D':
        y--;
        break;
      case 'L':
        x--;
        break;
      case 'R':
        x++;
        break;
      // diagonal moves are based on clock numbers:
      // T (ten) for top-left
      // O (one) for top-right
      // F (four) for bottom-right
      // S (seven) for bottom-left
      case 'T':
        x--; y++;
        break;
      case 'O':
        x++; y++;
        break;
      case 'F':
        x++; y--;
        break;
      case 'S':
        x--; y--;
        break;
      }

      if (log_motion) {
        log_position();
      }
    }

    void follow(int follow_x, int follow_y) {
      int x_dir = follow_x - x; 
      int y_dir = follow_y - y;
      if (x==follow_x && y==follow_y) {
        // do nothing
      } else if (x==follow_x && std::abs(y_dir) > 1) {
        // move along y-axis
        (y_dir < 0) ? move('D', 1) : move('U', 1);
        
      } else if (y==follow_y && std::abs(x_dir) > 1) {
        // move along x-axis
        (x_dir < 0) ? move('L', 1) : move('R', 1);
      } else if ((std::abs(x_dir) + std::abs(y_dir)) > 2) {
        // move diagonally
        if (x_dir < 0 && y_dir > 0) { move('T', 1); }
        if (x_dir > 0 && y_dir > 0) { move('O', 1); }
        if (x_dir > 0 && y_dir < 0) { move('F', 1); }
        if (x_dir < 0 && y_dir < 0) { move('S', 1); }
      }
    }

    std::string to_string() {
      std::string output = std::to_string(x) + "," + std::to_string(y);
      return output;
    }

    void log_position() {
      // log visited positions as strings for easy comparison
      visited_positions.push_back(to_string());
    }

    int number_visited_positions() {
      // make a copy to not alter the original data
      std::vector<std::string> vispos = visited_positions;

      // remove duplicate positions
      std::sort(vispos.begin(), vispos.end());
      vispos.erase(std::unique(vispos.begin(), vispos.end()), vispos.end());

      return vispos.size();
    }

    static void reset_log() {
      visited_positions = {};
    }

};

// initialize static variable
std::vector<std::string> RopeEnd::visited_positions = {};

void part_1() {
  // setup rope ends
  RopeEnd::reset_log();

  RopeEnd head = RopeEnd(0, 0);
  RopeEnd tail = RopeEnd(0, 0);
  tail.log_motion = true;
  head.follower = &tail;

  tail.log_position();


  // setup variables for loop
  std::ifstream input("input.txt");
  std::string line;
  char direction; int steps;

  while (getline(input, line)) {
    std::stringstream string_in(line);
    string_in >> direction >> steps;
    head.move(direction, steps);
    // std::cout << direction << ", " << steps << std::endl;
  }

  std::cout << head.number_visited_positions() << std::endl;
}

void part_2(int n_knots=1) {
  // setup rope ends
  RopeEnd::reset_log();

  RopeEnd knots[10] = {};

  for (int i = 0; i < n_knots; i++) {
    knots[i] = RopeEnd(0,0);

    // assign followers
    if (i > 0) {
      knots[i - 1].follower = &(knots[i]);
    }

    // log the positions of the last knot
    if (i == n_knots - 1)
    {
      knots[i].log_motion = true;
      knots[i].log_position();
    }
    
  }
    
  // setup variables for loop
  std::ifstream input("input.txt");
  std::string line;
  char direction; int steps;

  while (getline(input, line)) {
    std::stringstream string_in(line);
    string_in >> direction >> steps;
    // move the head
    knots[0].move(direction, steps);
  }

  std::cout << knots[0].number_visited_positions() << std::endl;
}

int main() {
  part_1();
  part_2(10);

  return 0;
}
