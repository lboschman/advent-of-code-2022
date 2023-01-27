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
    char c;
    bool visited = false;
    // arbitrarily high value, but that way I won't have to check if distance
    // has already been assigned.
    int dist = 9001;
    
    Point() = default;
  
    Point(int x, int y, int z) : x(x), y(y), z(z) {};

    Point(int x, int y, char c) : x(x), y(y), c(c) {
      // Startpoint is 0, eindpoint = 27
      if (c=='S') {
        z = 1;
      } else if (c=='E') {
        z = 26;
      } else {
        //'a' should be at 1
        z = (c - 'a') + 1;
      }

      if (c=='a') {
        dist = 0;
      }
    }

    void reset(bool any_a_point=false) {
      visited = false;
      int standard = 9001;
      dist = (c=='S') ? 0 : 9001;
      if (any_a_point) {
        dist = (c=='a') ? 0 : 9001;
      }
    }

};

class Landscape {
  public:
    std::vector<std::vector<Point*> > grid;
    std::vector<Point*> unvisited = {};
    

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

    std::vector<Point*> find_acc_unvisited_neighbours(Point *p) {
      std::vector<Point*> acc_neighbours = find_accessible_neighbours(p);
      std::vector<Point*> unvisited_neighbours = {};
      for (Point *mp : acc_neighbours) {
        if (! mp->visited) {unvisited_neighbours.push_back(mp);}
      }

      return unvisited_neighbours;
    }

    Point* find_start_point() {
      Point* startpoint = nullptr;

      for (auto row : grid) {
        for (Point* p: row) {
          if (p->c == 'S') {
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
          if (p->c == 'E') {
            endpoint = p;
          }
        }
      }

      return endpoint;
    }

    void reset_points(bool any_a_points=false) {
      for (auto row : grid) {
        for (Point* p : row) {
          p->reset(any_a_points);
        }
      }
      // create the unvisited set
      unvisited.clear();
      for (auto row : grid) {
        unvisited.insert( unvisited.end(), row.begin(), row.end());
      }
    }

    static bool is_closer(const Point* p1, const Point* p2) {
      return p1->dist < p2->dist;
    }

    int find_shortest_route(bool make_hiking_trail=false) {
      reset_points(make_hiking_trail);
      
      Point *start, *current, *end;
      start = find_start_point();
      end = find_end_point();
      start->dist = 0;
      std::sort(unvisited.begin(), unvisited.end(), is_closer);

      while (!end->visited) {
        current = unvisited[0];
        visit_node(current);
      }
      
      return end->dist;
    }

    void visit_node(Point *p) {
      std::vector<Point*> unvis_neighbours = find_acc_unvisited_neighbours(p);
      // std::cout << "Visiting point " << p->x << ", " << p->y << std::endl;
      for (Point *np : unvis_neighbours) {
        if (np->dist > (p->dist + 1)) {
          np->dist  = p->dist + 1;
          // std::cout << "Point " << np->x << ", " << np->y << " set to dist: " << np->dist << std::endl;
          // std::cin.get();
        }
        // np->dist = (np->dist > p->dist + 1) ? p->dist + 1 : np->dist;
        
      }
      p->visited = true;
      std::remove(unvisited.begin(), unvisited.end(), p);
      std::sort(unvisited.begin(), unvisited.end(), is_closer);
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

  int distance = ls->find_shortest_route();

  std::cout << "Shortest route: " << distance << std::endl;

  distance = ls->find_shortest_route(true);

  std::cout << "Shortest hike : " << distance << std::endl;



  return 0;
}