#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>


struct Position {
  int x;
  int y;

  Position(int px, int py) {
    x = px;
    y = py;
  }

  bool operator==(const Position&) const = default;
};

class RopeEnd {
  public:
    int x;
    int y;
    RopeEnd* follower = nullptr;

    static std::vector<std::string> visited_positions;

    RopeEnd(int px, int py) {
      x = px;
      y = py;
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
      }

      log_position();
    }

    void follow(int follow_x, int follow_y) {
      if (x==follow_x && y==follow_y) {
        // do nothing
      } else if (x==follow_x && std::abs(y - follow_y) > 1) {
        // move along y-axis
        y += (follow_y - y) / std::abs(y - follow_y);
      } else if (y==follow_y && std::abs(x - follow_x) > 1) {
        // move along x-axis
        x += (follow_x - x) / std::abs(x - follow_x);
      } else if ((std::abs(x - follow_x) + std::abs(y - follow_y)) > 2) {
        // move diagonally
        x += (follow_x - x) / std::abs(follow_x - x);
        y += (follow_y - y) / std::abs(follow_y - y);
      }
      
      log_position();

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
      std::vector<std::string> vispos = visited_positions;

      // get the unique positions
      std::sort(vispos.begin(), vispos.end());
      vispos.erase(std::unique(vispos.begin(), vispos.end()), vispos.end());

      return vispos.size();
    }

    static void reset_log() {
      visited_positions = {};
    }

};

std::vector<std::string> RopeEnd::visited_positions = {};

void part_1() {
  std::ifstream input("input.txt");

  RopeEnd::reset_log();

  RopeEnd head = RopeEnd(0, 0);
  RopeEnd tail = RopeEnd(0, 0);

  head.follower = &tail;


}



int main() {

  RopeEnd::reset_log();


  RopeEnd pos = RopeEnd(1, 5);
  RopeEnd tail = RopeEnd(0, 5);

  pos.follower = &tail;

  pos.log_position();

  std::cout << pos.x << ", " << pos.y << std::endl;
  std::cout << tail.x << ", " << tail.y << std::endl;
  std::cout << "Visited positions: " << pos.number_visited_positions() << std::endl;
  std::cout << "==========" << std::endl;

  pos.move('U', 3);
  std::cout << pos.x << ", " << pos.y << std::endl;
  std::cout << tail.x << ", " << tail.y << std::endl;
  std::cout << "Visited positions: " << pos.number_visited_positions() << std::endl;
  std::cout << "==========" << std::endl;

  pos.move('L', 3);
  std::cout << pos.x << ", " << pos.y << std::endl;
  std::cout << tail.x << ", " << tail.y << std::endl;
  std::cout << "Visited positions: " << pos.number_visited_positions() << std::endl;
  std::cout << "==========" << std::endl;

  pos.move('R', 3);
  std::cout << pos.x << ", " << pos.y << std::endl;
  std::cout << tail.x << ", " << tail.y << std::endl;
  std::cout << "Visited positions: " << pos.number_visited_positions() << std::endl;
  std::cout << "==========" << std::endl;

  return 0;
}
