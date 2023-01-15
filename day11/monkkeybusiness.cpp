#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>


class Monkey {
  public:

    static std::vector<Monkey> all_monkeys;

    bool worry_level_additive = false;
    int worry_level_multiplier_additive = 0;
    int test_divisor = 0;
    int test_true_receiver = 0;
    int test_false_receiver = 0;
    std::vector<int> items;

    int inspections = 0;

    Monkey(){
      all_monkeys.push_back(*this);
    }
    
    int intermediate_worry_level(int old) {
      if (worry_level_additive) {
        return old + worry_level_multiplier_additive;
      } else {
        return old * worry_level_multiplier_additive;
      }
    }

    int new_worry_level(int old) {
      int intermediate = intermediate_worry_level(old);
      inspections++;
      // std::cout << inspections << std::endl;
      int new_worry = intermediate / 3;
      return new_worry;
    }

    Monkey* monkey_pointer(int index) {
      return &(all_monkeys[index]);
    }

    int which_monkey_to_throw_to(int worry_level) {
      return (worry_level % test_divisor == 0) ? test_true_receiver : test_false_receiver;
    }

    void throw_item() {
      int current_item = items[0];
      int new_worry = new_worry_level(current_item);

      int to_monkey = which_monkey_to_throw_to(new_worry);

      monkey_pointer(to_monkey)->items.push_back(new_worry);

      items.erase(items.begin());

    }

    void throw_all_items() {
      while (items.size() > 0) {
        throw_item();
      }
    }
};

std::vector<Monkey> Monkey::all_monkeys = {};

void part_1() {
  std::ifstream input("input.txt");
  std::string line;
  int index = 0;
  while (getline(input, line)) {
    // if (line[0]=='M') {
    Monkey m = Monkey();
    Monkey* mp =&(Monkey::all_monkeys[index]);
    // }
    std::string arg0, arg1, arg2, arg3, arg4, arg5;
    
    // Get the starting items;
    getline(input, line);
    std::stringstream stream0(line);
    stream0 >> arg0 >> arg1;
    int item_int;
    while (stream0 >> item_int)
    {
      stream0 >> arg2;
      mp->items.push_back(item_int);
    }

    // do the new-worry-score operation
    getline(input, line);
    std::stringstream stream1(line);
    stream1 >> arg0 >> arg1 >> arg2 >> arg3;
    char operation; int quantity;
    stream1 >> operation >> quantity;
    if (operation=='+') {
      mp->worry_level_additive = true;
    }
    mp->worry_level_multiplier_additive = quantity;

    // devise the test
    getline(input, line);
    std::stringstream stream2(line);
    stream2>> arg0 >> arg1 >> arg2;
    int test_quantity;
    stream2 >> test_quantity;
    mp->test_divisor = test_quantity;

    // monkey that receives in case of true
    getline(input, line);
    std::stringstream stream3(line);
    stream3 >> arg0 >> arg1 >> arg2 >> arg3 >> arg4;
    int true_receiving_monkey;
    stream3 >> true_receiving_monkey;
    mp->test_true_receiver = true_receiving_monkey;

    // monkey that receives in case of false
    getline(input, line);
    std::stringstream stream4(line);
    stream4 >> arg0 >> arg1 >> arg2 >> arg3 >> arg4;
    int false_receiving_monkey;
    stream4 >> false_receiving_monkey;
    mp->test_false_receiver = false_receiving_monkey;

    getline(input, line);
    index++;
  }

  // for (Monkey m1 : Monkey::all_monkeys) {
  //   for (int item : m1.items) {
  //     std::cout << item << " ";
  //   }
  //   std::cout << std::endl;
  //   std::cout << m1.worry_level_additive << ": " << m1.worry_level_multiplier_additive << std::endl;
  //   std::cout << m1.test_divisor << " ? " << m1.test_true_receiver << " : " << m1.test_false_receiver << std::endl;
  //   std::cout << "====================" << std::endl;
  // }


  int cycle = 0;
  int max_cycles = 20;

  while (cycle < max_cycles) {
    for (int i=0; i<Monkey::all_monkeys.size(); i++) {
      Monkey::all_monkeys[i].throw_all_items();
      // m.throw_all_items();
    }
    std::cout << "Finished cycle: " << cycle << std::endl;
    cycle++;
  }

  std::vector<int> inspections = {};
  for (Monkey m : Monkey::all_monkeys) {
    inspections.push_back(m.inspections);
  }

  std::sort(inspections.begin(), inspections.end(), std::greater<>());

  std::cout << inspections[0] * inspections[1] << std::endl;

}

int main() {
  part_1();
  return 0;
}