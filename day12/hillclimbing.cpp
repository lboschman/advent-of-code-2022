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
      // Startpoint is 0, eindpoint = 27
      if (c=='S') {
        z = 0;
      } else if (c=='E') {
        z = 27;
      } else {
        // 'a' should be offset by 1 from the start-point
        z = (c - 'a') + 1;
      }
    }
};

class Landscape {
  public:
    std::vector<std::vector<Point*> > grid;

    void add_point(Point* p) {
      // if necessary, expand grid to accomodate new point
      while (grid.size() < p->x + 1) {
        grid.push_back(std::vector<Point*>());
      }
      while (grid[p->x].size() < p->y + 1) {
        Point temp = Point();
        grid[p->x].push_back(&temp);
      }
      // add point in grid
      grid[p->x][p->y] = p;
    }

    std::vector<Point*> find_neighbours(Point* p) {
      // find all neighbours in cardinal directions
      // beware of edge-cases
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
      // find all neighbours with a height-difference no more than 1
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
      // find all neighbours with a height-difference no more than 1
      return find_accessible_neighbours(grid[x][y]);
    }

    Point* find_start_point() {
      Point* startpoint = nullptr;

      for (auto row : grid) {
        for (Point* p: row) {
          if (p->z == 0) {
            startpoint = p;
          }
        }
      }

      return startpoint;
    }

    Point* find_end_point() {
      Point* endpoint = nullptr;
      for (auto row : grid) {
        for (Point* p: row) {
          if (p->z == 27) {
            endpoint = p;
          }
        }
      }

      return endpoint;
    }
};




Landscape* create_grid() {
  std::ifstream input("input.txt");
  Landscape *grid = new Landscape();
  std::string line;
  int linenumber = 0;
  
  while (getline(input, line)) {
    for (int i = 0; i < line.size(); i++)
    {
      // convention: linenumber is y-coordinate
      // position in line is x-coordinate
      Point *p = new Point(i, linenumber, line[i]);
      grid->add_point(p);
    }
    linenumber++;
  }

  return grid;
}


int main() {
  Landscape* ls = create_grid();
  
  // just a small check
  Point *mp = ls->find_start_point();
  std::cout << mp->x << ", " << mp->y << ": " << mp->z << std::endl;

  mp = ls->find_end_point();
  std::cout << mp->x << ", " << mp->y << ": " << mp->z << std::endl;


  return 0;
}