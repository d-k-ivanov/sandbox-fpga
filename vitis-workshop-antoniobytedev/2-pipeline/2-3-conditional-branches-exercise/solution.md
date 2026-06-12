# SOLUTION
```cpp
#define SIZE 256
#define TOKENS 64

void count_tokens(int stream[SIZE], int counts[TOKENS]) {
    int acc = 0;
    int old_token = stream[0];
    int current;

#pragma HLS DEPENDENCE variable=counts intra RAW false
    for (int i = 0; i < SIZE; i++) {
#pragma HLS PIPELINE II=1
        current = stream[i];
        if (current == old_token) {
            acc++;
        } else {
            counts[old_token] = acc;
            acc = counts[current] + 1;  // False dependency here if old_token ≠ current
        }
        old_token = current;
    }

    counts[old_token] = acc;
}
```
The pipeline violation occurs because Vitis HLS detects a potential Read-After-Write (RAW) dependency in the hist array inside the loop. Specifically, it sees a write to hist[old] followed by a read from hist[val] in the else branch. Although the if (old == val) condition guarantees these accesses target different addresses, Vitis cannot verify this at compile time and conservatively assumes a conflict. This prevents it from safely starting a new iteration every cycle, increasing the initiation interval (II) above 1.

Here we can see that by applying pipeline and removing the false dependency we were able to reduce the number of cycles by a factor of 20.
## Finished table
| Metric                        | **Without Pipelining** | **With `#pragma HLS PIPELINE`** | **Pipelined and Fixed Dependency** |
| ----------------------------- | ---------------------- | ------------------------------- | ---------------------------------- |
| **Total Latency (cycles)**    |          1538              |              520                   |      264                              |
| **LUTs Used**                 |  209                      |             326                    |           325                         |
| **FFs Used**                  |  123                      |            197                     |       307                             |
| **DSPs Used**                 |    0                    |      0                           |     0                               |
| **BRAMs Used**                |     0                   |     0                            |  0                                  |

