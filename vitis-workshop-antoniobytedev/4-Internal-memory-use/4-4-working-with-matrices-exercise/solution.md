# Solution
```cpp
void matvec_mult(int A[64][64], int x[64], int y[64]) {
    #pragma HLS ARRAY_PARTITION variable=A dim=2 type=complete
    for (int i = 0; i < 64; i++) {
        int sum = 0;
        #pragma HLS PIPELINE II=1
        for (int j = 0; j < 64; j++) {

            sum += A[i][j] * x[j];
        }
        y[i] = sum;
    }
}
```

By partitioning the correct dimension we can increase the throughput exponentially. This solution can be improved further by replacing the complete partitioning by a cyclic partitioning with factor=2, achieving the same throughput with a much lower area.
## Finished table
| Metric                        | **Without Partitioning** | **With Complete partitioning** 
| ----------------------------- | ---------------------- | ------------------------------- | 
| **Total Latency (cycles)**    |          2087            |        105  |                                                        
| **LUTs Used**                 |     2276                   | 4060                                |                        
| **FFs Used**                  |        3003                |     6911                          | 
|**DSPs Used**                  |      6                  |192  |
**BRAMs Used**|0|0|

