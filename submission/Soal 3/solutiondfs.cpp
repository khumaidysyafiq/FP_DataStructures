// solution.cpp — DFS (Depth-First Search)
//
// Compile: g++ -O2 -std=c++17 solution.cpp -o solution
// Run:     ./solution ../maps/soal1.txt output.txt

#include "harness.h"
#include <stack>
#include <set>

vector<Cell> solve(vector<vector<char>>& grid, Cell start, Cell goal){
  vector<Cell> visited;

  int dr[] = {-1, 1, 0, 0};
  int dc[] = { 0, 0,-1, 1};

  stack<Cell> s;      
  set<Cell> seen;     

  s.push(start);
  came_from[start] = start;

  while (!s.empty()) {
    Cell current = s.top();  
    s.pop();

    if (seen.count(current)) continue;
    seen.insert(current);

    visited.push_back(current);
    if (current == goal) break;
    int r = current.first;
    int c = current.second;

    for (int k = 0; k < 4; k++) {
      int nr = r + dr[k];
      int nc = c + dc[k];

      if (!inBounds(nr, nc)) continue;
      if (isWall(grid[nr][nc])) continue;

      Cell neighbor = {nr, nc};
      if (seen.count(neighbor)) continue;

      came_from[neighbor] = current;
      s.push(neighbor);
    }
  }

  return visited;
}