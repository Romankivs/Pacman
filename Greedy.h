#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <stack>

#include "Direction.h"

using namespace std;

namespace Greedy
{
    struct Cell {
        Cell(int r, int c, int h) : row(r), col(c), h(h) {}
        int row;
        int col;
        int h;
    };

    struct CompareCells {
        bool operator()(const Cell& a, const Cell& b) {
            return a.h > b.h;
        }
    };

    int greedyBestFirstSearch(const vector<vector<bool>>& grid, const Cell& start, const Cell& goal) {
        int rows = grid.size();
        int cols = grid[0].size();

        priority_queue<Cell, vector<Cell>, CompareCells> pq;
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));

        vector<vector<Cell>> parent(rows, vector<Cell>(cols, Cell(-1, -1, -1)));

        pq.push(start);

        while (!pq.empty()) {
            Cell current = pq.top();
            pq.pop();

            int row = current.row;
            int col = current.col;

            if (row == goal.row && col == goal.col) {
                std::cout << "Goal cell found!" << endl;

                // Trace back the path
                stack<Cell> path;
                Cell currentCell = goal;
                while (!(currentCell.row == start.row && currentCell.col == start.col)) {
                    path.push(currentCell);
                    currentCell = parent[currentCell.row][currentCell.col];
                }

                path.push(start);

                if (path.size() <= 1)
                    return -1;

                std::cout << "Path: ";
                auto first = path.top();
                std::cout << "(" << first.row << ", " << first.col << ") ";

                path.pop();
                auto second = path.top();
                int res = findDirection({ first.row, first.col }, { second.row, second.col });

                while (!path.empty()) {
                    Cell cell = path.top();
                    std::cout << "(" << cell.row << ", " << cell.col << ") ";
                    path.pop();
                }
                std::cout << endl;

                return res;
            }

            visited[row][col] = true;

            // up, down, left, right
            int dr[] = { 1, -1, 0, 0 };
            int dc[] = { 0, 0, 1, -1 };

            for (int i = 0; i < 4; ++i) {
                int newRow = row + dr[i];
                int newCol = col + dc[i];

                if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && !grid[newRow][newCol] && !visited[newRow][newCol]) {
                    int hNew = abs(newRow - goal.row) + abs(newCol - goal.col);
                    parent[newRow][newCol] = current;
                    pq.push(Cell(newRow, newCol, hNew));
                }
            }
        }

        std::cout << "Goal cell not found!" << endl;
        return -1;
    }

}
