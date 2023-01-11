#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>


class Monitor {
  public:
    int cycle = 1;
    int X = 1;

    int cumulative_signal_strength = 0;
    bool draw = false;
    int screenwidth = 40;
    
    Monitor() {
      cycle = 1;
      X = 1;
      cumulative_signal_strength = 0;
    }

    void cycle_monitor() {
      if ((cycle - 20) % 40 == 0) {
        cumulative_signal_strength += cycle * X;
      }

      if (draw) {
        draw_pixel();
      }

      cycle++;
    }

    void draw_pixel() {
      int hor_pos = (cycle - 1) % screenwidth;
      char draw_char;
      if (std::abs(X - hor_pos) <= 1) {
        draw_char = '#';
      } else {
        draw_char = '.';
      }

      std::cout << draw_char;
      
      if (hor_pos==screenwidth-1) {
        std::cout << std::endl;
      }
    }

    void noop() {
      cycle_monitor();
    }

    void addx(int value) {
      cycle_monitor();
      cycle_monitor();
      X += value;
    }
};

void part_1() {
  Monitor monitor = Monitor();
  std::ifstream input("input.txt");
  std::string line, command;
  int argument;

  while (getline(input, line)) {
    std::stringstream stream(line);
    stream >> command >> argument;
    if (command=="noop") {
      monitor.noop();
    } else {
      monitor.addx(argument);
    }
  }

  std::cout << monitor.cumulative_signal_strength << std::endl;
}

void part_2() {
  Monitor monitor = Monitor();
  monitor.draw = true;

  std::ifstream input("input.txt");
  std::string line, command;
  int argument;

  while (getline(input, line)) {
    std::stringstream stream(line);
    stream >> command >> argument;
    if (command=="noop") {
      monitor.noop();
    } else {
      monitor.addx(argument);
    }
  }

}


int main() {
  part_1();
  part_2();
  return 0;
}