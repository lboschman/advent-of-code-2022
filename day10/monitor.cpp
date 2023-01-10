#include <string>
#include <iostream>
#include <fstream>
#include <sstream>


class Monitor {
  public:
    int cycle = 1;
    int X = 1;

    int cumulative_signal_strength = 0;

    Monitor() {
      cycle = 1;
      X = 1;
      cumulative_signal_strength = 0;
    }

    void cycle_monitor() {
      if ((cycle - 20) % 40 == 0) {
        cumulative_signal_strength += cycle * X;
      }

      cycle++;
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


int main() {
  part_1();
  return 0;
}