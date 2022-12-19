#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

class container_stack
{
private:
    std::vector<char> containers;
public:
    // container_stack(/* args */);
    // ~container_stack();

    void add_container(char container) {
        containers.push_back(container);
    }

    char remove_container() {
        int pos = containers.size() - 1;
        char output = containers[pos];
        containers.pop_back();
        return output;
    }

    void reverse() {
        std::vector<char> reverse_stack;
        for (int i = 0; i < containers.size(); i++){
            reverse_stack.push_back(containers[containers.size() - i - 1]);
        }

        containers = reverse_stack;
    }

    char top_container() {
        return containers[containers.size() - 1];
    }
};


class multi_stacks {
private:
    std::vector<container_stack> stacks;

public:
    // multi_stacks();
    // ~multi_stacks();
    void move_container(int origin, int destination) {
        int orig = origin - 1;
        int dest = destination - 1;
        char container = stacks[orig].remove_container();
        stacks[dest].add_container(container);
    }

    void move_multiple_containers(int origin, int destination, int quantity) {
        for (int i = 0; i < quantity; i++)
        {
            move_container(origin, destination);
        }
        
    }

    void add_stack() {
        container_stack new_stack;
        stacks.push_back(new_stack);
    }

    void add_container(int stack, char container) {
        stacks[stack - 1].add_container(container);
    }

    void reverse_containers() {
        for (auto & element : stacks) {
            element.reverse();
        }
    }

    std::string read_top_containers() {
        std::string message = "";
        for (auto & element : stacks)
        {
            message.push_back(element.top_container());
        }
        return message;   
    }
};

multi_stacks parse_input() {
    std::ifstream input("input.txt");
    std::string line = "";
    
    getline(input, line);
    int number_stacks = (line.length() + 1) / 4;

    multi_stacks stacks;
    for (int i = 0; i < number_stacks; i++){
        stacks.add_stack();
    }

    while (line[1]!='1') {
        for (int i = 0; i < number_stacks; i++)
        {
            int index = 1 + (4 * i);
            char container = line[index];
            if (container != ' ') {
                stacks.add_container(i + 1, container);
            }
        }

        getline(input, line);
        
    }

    stacks.reverse_containers();
    getline(input, line);

    while (getline(input, line)) {
    
        std::stringstream linestring(line);
        std::string instruction_part;
        std::vector<std::string> linelist;

        while (getline(linestring, instruction_part, ' '))
        {
            linelist.push_back(instruction_part);
        }

        std::vector<int> instructions;
        for (int i = 1; i < 6; i += 2) {
            std::cout << linelist[i] << std::endl;
            instructions.push_back(std::stoi(linelist[i]));
        }
        
        stacks.move_multiple_containers(
            instructions[1], 
            instructions[2],
            instructions[0]
        );
    
    }
    return stacks;

}


int main() {
    multi_stacks stacks = parse_input();

    std::cout << stacks.read_top_containers() << std::endl;


    return 0;
}