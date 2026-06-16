// solution.cpp — THIS IS WHAT YOU WILL WORK ON.
//
// Write your algorithm ONLY inside the solve() function below.
// Do not add other functions. Do not modify harness.h.
//
// Compile: g++ -O2 -std=c++17 solution.cpp -o solution
// Run:     ./solution ../maps/soal1.txt output.txt
//          ./solution ../maps/soal2.txt output.txt
//          ./solution ../maps/soal3.txt output.txt
// View:    open engine/index.html, select the question/map, drag output.txt, click Play/Run.

#include "harness.h"
// Tambahkan include yang kalian butuhkan, contoh:
#include <queue>
#include <vector>
#include <map>

vector<Cell> solve(vector<vector<char>>& grid, Cell start, Cell goal){
  vector<Cell> visited;  // list of visited cells (ordered) — return this

  priority_queue<pair<int, Cell>, vector<pair<int, Cell>>, greater<pair<int, Cell>>> pq;
    
    map<Cell, int> dist;
    
    int dr[] = {-1, 1, 0, 0};
    int dc[] = { 0, 0,-1, 1};
    
    dist[start] = 0;
    pq.push({0, start});
    
    while (!pq.empty()) {
        auto [current_cost, current_cell] = pq.top();
        pq.pop();
        
        if (current_cost > dist[current_cell]) {
            continue;
        }
        
        visited.push_back(current_cell);
        
        if (current_cell == goal) {
            break;
        }
        
        int r = current_cell.first;
        int c = current_cell.second;
        
        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k];
            int nc = c + dc[k];
            Cell neighbor = {nr, nc};
            
            if (inBounds(nr, nc) && !isWall(grid[nr][nc])) {
                
                int step_cost = cellCost(grid[nr][nc]);
                int new_cost = current_cost + step_cost;
                
                if (dist.find(neighbor) == dist.end() || new_cost < dist[neighbor]) {
                    dist[neighbor] = new_cost;
                    
                    came_from[neighbor] = current_cell; 
                    
                    pq.push({new_cost, neighbor});
                }
            }
        }
    }

  // ===================== WRITE YOUR ALGORITHM HERE =====================
  //
  // Four movement directions (up, down, left, right):
  //   int dr[] = {-1, 1, 0, 0};
  //   int dc[] = { 0, 0,-1, 1};
  // Neighbor of cell (r,c) is calculated: nr = r + dr[k], nc = c + dc[k] (loop k = 0..3)
  //
  // Tools from harness.h that you can use:
  //   inBounds(nr, nc)         -> true if (nr,nc) is still inside the grid
  //   isWall(grid[nr][nc])     -> true if the cell is a wall (cannot be passed through)
  //   cellCost(grid[nr][nc])   -> cost to enter the cell: 1, or numbers 1-9 for weighted cells
  //
  // REQUIRED: every time you find a new neighbor to be processed, record its parent:
  //   came_from[neighbor] = current_cell;
  // Without this line, the final path cannot be reconstructed and the visualization tool will show FAILED.
  //
  // When a cell is processed, insert it into the exploration trace:
  //   visited.push_back(current_cell);
  //
  // =========================================================================
  return visited;
}
