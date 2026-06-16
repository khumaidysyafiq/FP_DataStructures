// solution.cpp — THIS IS WHAT YOU WILL WORK ON.
//
// Write your algorithm ONLY inside the solve() function below.
// Do not add other functions. Do not modify harness.h.
//
// Compile: g++ -O2 -std=c++17 D:\FP\submission\solution.cpp -o D:\FP\submission\output\solution.exe
// Run:     D:\FP\submission\output\solution.exe D:\FP\maps\soal1.txt D:\FP\submission\output\output.txt
// View:    open engine/index.html, select the question/map, drag output.txt, click Play/Run.

#include "harness.h"
#include <queue>
#include <set>


vector<Cell> solve(vector<vector<char>>& grid, Cell start, Cell goal){
  vector<Cell> visited;

int dr[] = {-1, 1, 0, 0};
int dc[] = { 0, 0,-1, 1};

queue<Cell> q;
set<Cell> seen;

q.push(start);
seen.insert(start);

while (!q.empty()) {
  Cell current = q.front();
  q.pop();

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

    seen.insert(neighbor);
    came_from[neighbor] = current;
    q.push(neighbor);
  }
}
  return visited;
}
