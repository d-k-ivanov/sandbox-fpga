

# Solution
```cpp
#define ROWS 8
#define COLS 64

void top_function(int A[ROWS][COLS], int B[ROWS][COLS]) {
#pragma HLS ARRAY_RESHAPE variable=A type=cyclic factor=8 dim=2
#pragma HLS ARRAY_RESHAPE variable=B type=cyclic factor=8 dim=2

    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            #pragma HLS PIPELINE II=1
            #pragma HLS UNROLL factor=16
            B[r][c] = A[r][c] * 2;
        }
    }
}
```
By reshaping the memory not only is our architecture faster but it also consumes less area, as more data can be stored in the same amount of memory blocks, making this the superior architecture.
## Finished table
| Metric                        | **Without Reshaping** | **With Reshaping** 
| ----------------------------- | ---------------------- | ------------------------------- | 
| **Total Latency (cycles)**    |        259               |              34                   |                                    |
| **LUTs Used**                 |   437                    |           153                      |                                    |
| **FFs Used**                  | 235                       |      33                           |                                    |
 **BRAMs used**                  |   0                     |            0                     |
 |**DSP used**|0|0||

