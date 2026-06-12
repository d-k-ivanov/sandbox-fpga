# Solution
```cpp
#define N 128
void bubble_sort(int A[N]) {
    #pragma HLS ARRAY_PARTITION variable=A dim=1 type=complete   
    for (int i = 0; i < N - 1; i++) {
        #pragma HLS PIPELINE II=1
        for (int j = 0; j < N - 1; j++) {
            int tmp=A[j];
            A[j] = (A[j]>A[j+1]) ? A[j+1] : A[j];
            A[j+1]=(A[j]>A[j+1]) ? tmp : A[j+1];
        }
    }
}
```

By comparing both architectures we can see that despite being similar in throughput area after refactoring is significantly smaller. It is recommended to avoid if statements when possible, as they can create bottlenecks and increase area, specially when combined with pragmas such as pipeline or unroll.
## Finished table
| Metric                        | **Without Refactoring** | **With refactoring** | 
| ----------------------------- | ------------------------------- | ---------------------------------- |
| **Total Latency (cycles)**    |      132               |              128                   |                                    |
| **LUTs Used**                 |   25040                     |           10214                    |                                    |
| **FFs Used**                  |   12302                     |          8170                      |                                    |
| **DSPs Used**                 |   0                     |         0                        |                                    |
| **BRAMs Used**                |     0                   |           0                      |                                    |