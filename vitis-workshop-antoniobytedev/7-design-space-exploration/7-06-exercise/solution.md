# Solution
1 This generates an architecture that automatically flattens the init loop, but it doesn't unroll the navigation loop. 


2 This architecture, due to its many memory accesses in both dimensions and use of conditionals makes this very hard to optimize. This makes it so when we choose to romove parallelism throughput actually increases, while resource usage decreases.
```cpp
#define N 64

void greedy_min_cost(int grid[N][N], int *total_cost) {
    int visited[N][N];


    // Initialize visited array
    init_loop_i: for (int i = 0; i < N; i++) {
        init_loop_j: for (int j = 0; j < N; j++) {
            #pragma HLS PIPELINE off
            visited[i][j] = 0;
        }
    }

    int x = 0;
    int y = 0;
    *total_cost = grid[0][0];
    visited[0][0] = 1;

navigation_loop:
    for(int moves = 0; moves < N*N; moves++) {
        #pragma HLS PIPELINE off
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

```

3 Because of what we discussed last exercise it is impossible to achieve 4 times more throughput than point 2 due to the large number of memory accesses and if statements, making the attempt to increase the throuhgput incredibly inefficient.
```cpp
#define N 64

void greedy_min_cost(int grid[N][N], int *total_cost) {
    int visited[N][N];

    #pragma HLS ARRAY_PARTITION variable=grid dim=2 type=cyclic factor=2
    #pragma HLS ARRAY_PARTITION variable=visited dim=2 type=cyclic factor=2
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
        #pragma HLS PIPELINE II=1
        #pragma HLS UNROLL factor=4
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

```
4


| metric          | Baseline | Fully Iterative | Latency Reduction(Parallelization) |
| --------------- | -------- |-----------------| ---------------------------------- |
| Latency(Cycles) | 167989   |       28802        |            16406                        |
| LUTs            |     6135 |     1734         |                 7276                   |
| FFs             |     5843 |      527          |                   1755                 |
| DSPs            |      9    |      0           |                    0                |
| BRAMs           |      3    |        1         |            2                        |

Because of what was mentioned before, the best option overall is the fully iterative as it's not only faster than baseline but uses less resources than it. Latency reduction is faster but needs 5 times more resources for twice the throughput, which makes it not worth it. However, dependending on your objectives you may prefer the fully iterative or the latency reduction versions.
