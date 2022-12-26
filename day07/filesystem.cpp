#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <variant>
#include <map>
#include <list>

class Directory;

class FileSystemElement {
    private:
        int size;

    public:
        Directory* parent;
        std::string name;
        int get_size(){
            return size;
        }

        FileSystemElement() = default;

        FileSystemElement(std::string new_name, Directory* new_parent) {
            name = new_name;
            parent = new_parent;
            size = 0;
        }
        FileSystemElement(std::string new_name, Directory* new_parent, int new_size);
        //  {
        //     name = new_name;
        //     parent = new_parent;
        //     size = new_size;
        //     if (new_parent != nullptr) {
        //         new_parent->add_child(*this);
        //     }
        // }

};
class Directory;
class File : public FileSystemElement{
    public:
        File(std::string new_name, Directory* new_parent, int new_size)
            : FileSystemElement(new_name, new_parent, new_size) {}
};

class Directory : public FileSystemElement
{
private:
    // static std::vector<Directory*> all_directories;
    static std::list<Directory*> all_directories_;

    std::map<std::string, FileSystemElement*> children;
    // std::vector<FileSystemElement*> children;

public:
    // Directory() {
    //     name = "/";
    //     parent = nullptr;
    //     all_directories.push_back(this);
    // }

    Directory() = default;

    Directory(std::string dirname, Directory *new_parent) {
        name = dirname;
        all_directories_.push_back(this);
        parent = new_parent;
        if (new_parent != nullptr) {
            new_parent->add_child(*this);
        }
    }

    static std::list<Directory*> all_directories() {
        return all_directories_;
    }
    void add_child(FileSystemElement new_child);
    // void add_child(FileSystemElement new_child) {
    //     children.insert({new_child.name, &new_child});
    // }

    // void create_child_dir(std::string new_name) {
    //     Directory new_child = Directory(new_name, this);
    //     // add_child(new_child);
    // }

    // void create_child_file(std::string new_name, int new_size=0) {
    //     File new_child = File(new_name, this, new_size);
    //     // add_child(new_child);
    // }

    // void create_child(std::string new_name, int new_size=0, bool file=true) {
    //     FileSystemElement new_child;
    //     // Directory* new_parent = this;
    //     if (file) {
    //         new_child = File(new_name, this, new_size);
    //     } else {
    //         new_child = Directory(new_name, this);
            
    //     }

    //     add_child(new_child);
    // }

    int get_size() {
        int total_size = 0;
        for (auto [child_name, child] : children) {
            total_size += child->get_size();
        }
        return total_size;
    }
};

std::list<Directory*> Directory::all_directories_;
inline void Directory::add_child(FileSystemElement new_child) {
        children.insert({new_child.name, &new_child});
    }

FileSystemElement::FileSystemElement(std::string new_name, Directory* new_parent, int new_size) {
            name = new_name;
            parent = new_parent;
            size = new_size;
            if (new_parent != nullptr) {
                new_parent->add_child(*this);
            }
        }


void parse_command(Directory cursor, std::string line) {

}

int part_1() {
    std::ifstream input("input.txt");

    Directory root = Directory("/", NULL);

    for (Directory* dir : Directory::all_directories()) {
        std::cout << dir->name << std::endl;
    }

    
    
    // Directory& cursor = root;

    // std::string line;

    // while (getline(input, line))
    // {
    //     /* code */
    // }
    
    return 0;

}

void change_string(std::string  &line) {
    std::string new_line = "Hello, I'm new";
    line = new_line;
}


int main()
{   
    std::string ok_line = "Hi, I'm very old";
    std::string* old_pointer = &ok_line;
    std::cout << ok_line << std::endl;
    change_string(ok_line);
    std::cout << ok_line << std::endl;
    
    part_1();

    return 0;
}