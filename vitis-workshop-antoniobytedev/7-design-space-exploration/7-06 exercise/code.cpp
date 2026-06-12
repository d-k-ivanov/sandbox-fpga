#include <stdint.h>

#define N 64   // Grid size

void greedy_min_cost(int grid[N][N], int *total_cost) {
    int visited[N][N];


    // Initialize visited array
    init_loop_i: for (int i = 0; i < N; i++) {
        init_loop_j: for (int j = 0; j < N; j++) {
            visited[i][j] = 0;
        }
    }

    int x = 0;
    int y = 0;
    *total_cost = grid[0][0];
    visited[0][0] = 1;

navigation_loop:
    for(int moves = 0; moves < N*N; moves++) {

        int best_cost = 99999;
        int next_x = x;
        int next_y = y;

        // Try move up
        if (x > 0 && !visited[x-1][y] && grid[x-1][y] < best_cost) {
            best_cost = grid[x-1][y];
            next_x = x-1; next_y = y;
        }
        // Try move down
        if (x < N-1 && !visited[x+1][y] && grid[x+1][y] < best_cost) {
            best_cost = grid[x+1][y];
            next_x = x+1; next_y = y;
        }
        // Try left
        if (y > 0 && !visited[x][y-1] && grid[x][y-1] < best_cost) {
            best_cost = grid[x][y-1];
            next_x = x; next_y = y-1;
        }
        // Try right
        if (y < N-1 && !visited[x][y+1] && grid[x][y+1] < best_cost) {
            best_cost = grid[x][y+1];
            next_x = x; next_y = y+1;
        }

        // If stuck, path ends
        if (next_x == x && next_y == y)
            break;

        // Move
        x = next_x;
        y = next_y;
        visited[x][y] = 1;
        *total_cost += grid[x][y];

        // If reached goal (bottom-right), exit
        if (x == N-1 && y == N-1)
            break;
    }
}
