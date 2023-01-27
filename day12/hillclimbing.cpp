#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>

class Point {
  public:
    int x;
    int y;
    int z;
    
    Point() = default;
  
    Point(int x, int y, int z) : x(x), y(y), z(z) {};

    Point(int x, int y, char c) : x(x), y(y) {
      if (c=='S') {
        z = 0;
      } else if (c=='E') {
        z = 27;
      } else {
        z = (c - 'a') + 1;
      }
    }
};

class Landscape {
  public:
    std::vector<std::vector<Point*> > grid;

    void add_point(Point* p) {
      while (grid.size() < p->x + 1) {
        grid.push_back(std::vector<Point*>());
      }
      while (grid[p->x].size() < p->y + 1) {
        Point temp = Point();
        grid[p->x].push_back(&temp);
      }
      grid[p->x][p->y] = p;
    }

    std::vector<Point*> find_neighbours(Point* p) {
      std::vector<Point*> neighbours;

      if (p->x > 0)
      {
        neighbours.push_back(grid[p->x - 1][p->y]);
      }
      if (p->x < grid.size() - 1) {
        neighbours.push_back(grid[p->x + 1][p->y]);
      }
      if (p->y > 0)
      {
        neighbours.push_back(grid[p->x][p->y - 1]);
      }
      if (p->y < grid[0].size() - 1) {
        neighbours.push_back(grid[p->x][p->y + 1]);
      }
    return neighbours;
    }

    std::vector<Point*> find_accessible_neighbours(Point* p) {
      std::vector<Point*> all_neighbours = find_neighbours(p);

      std::vector<Point*> acc_neighbours;

      for (Point *pn : all_neighbours) {
        if (pn->z - p->z <= 1) {
          acc_neighbours.push_back(pn);
        }
      }
      return acc_neighbours;
    }

    std::vector<Point*> find_accessible_neighbours(int x, int y) {
      return find_accessible_neighbours(grid[x][y]);
    }
    


};




void part1() {
  std::ifstream input("input.txt");
  Landscape grid = Landscape();
  std::string line;
  int linenumber = 0;
  
  while (getline(input, line)) {
    for (int i = 0; i < line.size(); i++)
    {
      Point *p = new Point(i, linenumber, line[i]);
      grid.add_point(p);
    }
    linenumber++;
  }

  Point *mp = grid.grid[0][0];
  std::cout << mp->x << ", " << mp->y << std::endl;


  // auto nb = grid.find_accessible_neighbours(7, 1);

  // for (auto element : nb) {
  //   std::cout << element->x << ", " << element->y << std::endl;
  // }

  
}


int main() {
  part1();
  return 0;
}