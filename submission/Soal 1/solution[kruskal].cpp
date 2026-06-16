// solution.cpp — THIS IS WHAT YOU WILL WORK ON.
//
// Write your algorithm ONLY inside the solve() function below.
// Do not add other functions. Do not modify harness.h.
//
// Compile: g++ -O2 -std=c++17 solution.cpp -o solution
// Run:     ./solution ../maps/soal1.txt output.txt
// View:    open engine/index.html, select the question/map, drag output.txt, click Play/Run.

#include "harness.h"
// Tambahkan include yang kalian butuhkan, contoh:
#include <queue>
#include <set>
#include <map>

vector<Cell> solve(vector<vector<char>>& grid, Cell start, Cell goal){
  vector<Cell> visited;  // list of visited cells (ordered) — return this
  
// ===================== WRITE YOUR ALGORITHM HERE =====================
  
  // 1. Cardinal movement directions (Strictly Up, Down, Left, Right)
  int dr[] = {-1, 1, 0, 0};
  int dc[] = { 0, 0,-1, 1};

  // Edge structure representation for Kruskal's minimum spanning tree
  struct GridEdge {
      Cell u, v;
      int weight;
      bool operator<(const GridEdge& other) const {
          return weight < other.weight;
      }
  };

  vector<GridEdge> edges;
  map<Cell, Cell> dsu_parent;

  // Initialize Disjoint Set Union (DSU) and gather all valid traversable edges
  for (int r = 0; r < rows_g; ++r) {
      for (int c = 0; c < cols_g; ++c) {
          if (isWall(grid[r][c])) continue; // Skip wall obstacles completely
          
          Cell curr = {r, c};
          dsu_parent[curr] = curr; // Self-parent initialization

          for (int k = 0; k < 4; ++k) {
              int nr = r + dr[k];
              int nc = c + dc[k];

              if (inBounds(nr, nc) && !isWall(grid[nr][nc])) {
                  Cell neighbor = {nr, nc};
                  
                  // Process each bidirectional edge exactly once
                  if (curr < neighbor) {
                      // Cost of the edge is the cost to enter the destination cell
                      int w = cellCost(grid[nr][nc]); 
                      edges.push_back({curr, neighbor, w});
                  }
              }
          }
      }
  }

  // Globally sort all edges by weight (The core greedy step of Kruskal's)
  sort(edges.begin(), edges.end());

  // Adjacency map to store our constructed Minimum Spanning Tree (MST)
  map<Cell, vector<Cell>> mst;

  // Build the MST using Kruskal's loop
  for (const auto& edge : edges) {
      // Find root of component U with path compression
      Cell rootU = edge.u;
      while (!(rootU == dsu_parent[rootU])) {
          rootU = dsu_parent[rootU];
      }
      Cell currU = edge.u;
      while (!(currU == rootU)) {
          Cell next = dsu_parent[currU];
          dsu_parent[currU] = rootU;
          currU = next;
      }

      // Find root of component V with path compression
      Cell rootV = edge.v;
      while (!(rootV == dsu_parent[rootV])) {
          rootV = dsu_parent[rootV];
      }
      Cell currV = edge.v;
      while (!(currV == rootV)) {
          Cell next = dsu_parent[currV];
          dsu_parent[currV] = rootV;
          currV = next;
      }

      // If they are in different components, unify them
      if (!(rootU == rootV)) {
          dsu_parent[rootU] = rootV;
          mst[edge.u].push_back(edge.v);
          mst[edge.v].push_back(edge.u);

          // Check if Start and Goal are now joined in the same tree component
          Cell rootStart = start;
          while (!(rootStart == dsu_parent[rootStart])) rootStart = dsu_parent[rootStart];
          
          Cell rootGoal = goal;
          while (!(rootGoal == dsu_parent[rootGoal])) rootGoal = dsu_parent[rootGoal];

          if (rootStart == rootGoal) {
              break; // Stop building immediately; our S-to-G path is guaranteed
          }
      }
  }

  // 3. Extract the final direct path using a clean traversal over the built MST
  queue<Cell> q;
  map<Cell, bool> visited_mst;

  q.push(start);
  visited_mst[start] = true;

  while (!q.empty()) {
      Cell current_cell = q.front();
      q.pop();

      // Log into the required visualization trace array
      visited.push_back(current_cell);

      if (current_cell == goal) break;

      // Move strictly along orthogonal MST tree paths
      for (const Cell& neighbor : mst[current_cell]) {
          if (!visited_mst[neighbor]) {
              visited_mst[neighbor] = true;
              came_from[neighbor] = current_cell; // Link step for harness path reconstruction
              q.push(neighbor);
          }
      }
  }

  // =========================================================================
  return visited;
}