# Solution
```cpp
void datapath1(int A[N], int B[N]) {
#pragma HLS LOOP_MERGE
int buffer[N];
copy_loop:
for (int i = 0; i < N; i++) {
    buffer[i] = A[i];
}


scale_loop:
for (int i = 0; i < N; i++) {
    B[i] = buffer[i] * 2 +5;
}

}
```
The loop can't be merged due to a carried dependency. B is written in the first loop and the written and read from in the second loop. The simplest way to fix this is to add a buffer and make it so that B is only written to in the second loop. By allowing both loops to merge not only do we achieve double throughput but also use less area, making this architecture better in every way.
## Finished Table
| Metric                        | **Without Refactoring** | **With Refactoring** 
| ----------------------------- | ---------------------- | ------------------------------- | 
| **Total Latency (cycles)**    |       264               |           131                      |                                    |
| **LUTs Used**                 |    351                    |       110                          |                                    |
| **FFs Used**                  |   94                     |         61                        |                                    |
|**BRAMs Used**|0|0
|**DSPs Used**|0|0