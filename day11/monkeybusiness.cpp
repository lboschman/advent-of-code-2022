#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

class Monkey {
  public:
    std::vector<int64_t> items;
    int64_t test_divisor;
    int64_t throw_to_when_true;
    int64_t throw_to_when_false;
    std::string operation;
    int64_t operation_modifier = 0;
    int64_t inspections = 0;
    static int64_t common_denominator;

    static std::vector<Monkey*> all_monkeys;

    static void set_denominator() {
      int nominator = 1;
      for (Monkey* m : all_monkeys) {
        nominator *= m->test_divisor;
      }
      common_denominator = nominator;
    }

    Monkey(){
      all_monkeys.push_back(this);
    }

    int64_t inspect_item(const int64_t item, const bool bored) {
      int64_t new_worry_level = operate(item);
      if (bored) {
        new_worry_level /= 3;
      } else {
        new_worry_level %= common_denominator;
      }

      inspections++;
      return new_worry_level;
    }

    int64_t operate(const int64_t item) {
      if (operation=="square") {
        return item * item;
      } else if (operation=="add")
      {
        return item + operation_modifier;
      } else {
        return item * operation_modifier;
      }
      
    }

    void throw_item(bool bored=true) {
      // pick the first item
      int64_t item = items[0];
      int64_t new_level = inspect_item(item, bored);
      if (new_level % test_divisor == 0) {
        all_monkeys[throw_to_when_true]->items.push_back(new_level);
      } else {
        all_monkeys[throw_to_when_false]->items.push_back(new_level);
      }

      items.erase(items.begin());
    }

    void throw_all_items(bool bored=true) {
      while (items.size() > 0)
      {
        throw_item(bored);
      }
      
    }
};

std::vector<Monkey*> Monkey::all_monkeys = {};
int64_t Monkey::common_denominator = 0;

void read_data() {
  std::ifstream input("input.txt");
  std::string line;
  int index = 0;
  while (getline(input, line)) {
    // if (line[0]=='M') {
    Monkey* m = new Monkey();
    Monkey* mp = Monkey::all_monkeys[index];
    // }
    std::string arg0, arg1, arg2, arg3, arg4, arg5;
    
    // Get the starting items;
    getline(input, line);
    std::stringstream stream0(line);
    stream0 >> arg0 >> arg1;
    int64_t item_int;
    while (stream0 >> item_int)
    {
      stream0 >> arg2;
      mp->items.push_back(item_int);
    }

    // do the new-worry-score operation
    getline(input, line);
    std::stringstream stream1(line);
    stream1 >> arg0 >> arg1 >> arg2 >> arg3;
    char operation; int64_t quantity;
    stream1 >> operation >> arg4;

    if (operation=='*' && arg4=="old") {
      mp->operation = "square";
    } else if (operation=='+') {
      mp->operation = "add";
      mp->operation_modifier = std::stoi(arg4);
    } else {
      mp->operation = "multiply";
      mp->operation_modifier = std::stoi(arg4);
    }

    // devise the test
    getline(input, line);
    std::stringstream stream2(line);
    stream2>> arg0 >> arg1 >> arg2;
    int64_t test_quantity;
    stream2 >> test_quantity;
    mp->test_divisor = test_quantity;

    // monkey that receives in case of true
    getline(input, line);
    std::stringstream stream3(line);
    stream3 >> arg0 >> arg1 >> arg2 >> arg3 >> arg4;
    int64_t true_receiving_monkey;
    stream3 >> true_receiving_monkey;
    mp->throw_to_when_true = true_receiving_monkey;

    // monkey that receives in case of false
    getline(input, line);
    std::stringstream stream4(line);
    stream4 >> arg0 >> arg1 >> arg2 >> arg3 >> arg4;
    int64_t false_receiving_monkey;
    stream4 >> false_receiving_monkey;
    mp->throw_to_when_false = false_receiving_monkey;

    getline(input, line);
    index++;
  }

  Monkey::set_denominator();
}

void throw_items(int64_t cycles, bool bored=true) {
  for (int64_t i = 0; i < cycles; i++)
  {
    for (Monkey* m : Monkey::all_monkeys) {
      m->throw_all_items(bored);
    }
  }
}

int64_t get_inspection_product() {
  std::vector<int64_t> inspections = {};
  for (Monkey* m : Monkey::all_monkeys) {
    inspections.push_back(m->inspections);
  }

  std::sort(inspections.begin(), inspections.end(), std::greater<>());
  return inspections[0] * inspections[1];

}

int main() {
  read_data();

  throw_items(10000, false);
  std::cout << get_inspection_product() << std::endl;

  for (Monkey* m : Monkey::all_monkeys) {
    std::cout << m->inspections << std::endl;
  }

  for (Monkey *m1 : Monkey::all_monkeys) {
    for (int64_t item : m1->items) {
      std::cout << item << " ";
    }
    std::cout << std::endl;
    std::cout << m1->operation << ": " << m1->operation_modifier << std::endl;
    std::cout << m1->test_divisor << " ? " << m1->throw_to_when_true << " : " << m1->throw_to_when_false << std::endl;
    std::cout << "====================" << std::endl;
  }

};