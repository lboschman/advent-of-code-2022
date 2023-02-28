#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <vector>
#include <set>
#include <memory>

struct Range {
  int min;
  int max;
};

struct Sensor {
  int x;
  int y;
  int x_beacon;
  int y_beacon;

  Sensor() = default;

  int max_manhattan_distance() {
    return std::abs(x - x_beacon) + std::abs(y - y_beacon);
  }

  Range positions(int y_pos) {
    int range = max_manhattan_distance() - std::abs(y - y_pos);
    Range output;
    output.min = x - range;
    output.max = x + range;

    return output;
  }

  std::vector<int> impossible_positions(int y_pos) {
    int range = max_manhattan_distance() - std::abs(y - y_pos);
    std::vector<int> values;
    for (int i = x - range; i <= x + range; i++) {
      values.push_back(i);
    }
    return values;
  }
  
};

int get_coord(std::stringstream& s) {
  int x;
  while (!std::isdigit(s.peek())) {
    s.ignore(1);
  }
  s >> x;
  return x;
}

std::vector<std::unique_ptr<Sensor>> parse_input(std::string filename) {
  std::ifstream input(filename);
  std::string line;

  std::vector<std::unique_ptr<Sensor>> sensors;

  while (getline(input, line))
  {
    std::stringstream s(line);
    std::unique_ptr<Sensor> sens = std::make_unique<Sensor>();
    sens.get()->x = get_coord(s);
    sens.get()->y = get_coord(s);
    sens.get()->x_beacon = get_coord(s);
    sens.get()->y_beacon = get_coord(s);
    
    sensors.push_back(std::move(sens));
  }

  return sensors;
  
}

int main() {
  auto sensors = parse_input("input_short.txt");
  auto s = sensors[0].get();

  std::cout << "x,y: " << s->x << "," << s->y << std::endl;
  return 0;
}