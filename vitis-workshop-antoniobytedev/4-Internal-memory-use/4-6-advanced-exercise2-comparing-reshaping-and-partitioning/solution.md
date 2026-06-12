# Solution
```cpp
#include <ap_int.h>
#define N 256

void top_function_partition(ap_int<32> A[N], ap_int<32> B[N], ap_int<32> C[N]) {
ap_int<32> buffer[N];
#pragma HLS ARRAY_PARTITION variable=B dim=1 type=cyclic factor=4
#pragma HLS ARRAY_PARTITION variable=C dim=1 type=cyclic factor=4
#pragma HLS ARRAY_PARTITION variable=buffer dim=1 type=cyclic factor=4
for(int i=0;i<N;i++)
{
#pragma HLS PIPELINE off
buffer[i]=A[i];
}
    for (int i = 0; i < N; i += 4) {
        for (int j = 0; j < 4; j++) {
            #pragma HLS UNROLL factor=4
            int idx = i + j;
            C[idx] = buffer[idx] + B[idx];
        }
    }
}

void top_function_reshape(ap_int<32> A[N], ap_int<32> B[N], ap_int<32> C[N]) {
ap_int<32> buffer[N];
#pragma HLS ARRAY_RESHAPE variable=B dim=1 type=cyclic factor=4
#pragma HLS ARRAY_RESHAPE variable=C dim=1 type=cyclic factor=4
#pragma HLS ARRAY_RESHAPE variable=buffer dim=1 type=cyclic factor=4
for(int i=0;i<N;i++)
{
#pragma HLS PIPELINE off
buffer[i]=A[i];
}
    for (int i = 0; i < N; i += 4) {
        for (int j = 0; j < 4; j++) {
            #pragma HLS UNROLL factor=4
            int idx = i + j;
            C[idx] = buffer[idx] + B[idx];
        }
    }
}
```
In this example we can achieve the same throughput using partitioning and reshaping. Reshaping needs more reousrces for the same throughput, making partitioning in this example the best option of the 2.
## Finished Table
| Metric                        | **Without Partitioning** | **With Partitioning** |**With Reshaping**
| ----------------------------- | ---------------------- | ------------------------------- | ------------------------------- | 
| **Total Latency (cycles)**    |      645                | 581  |      581                       |                                    |
| **LUTs Used**                 |   322        |     345       |           471                      |                                    |
| **FFs Used**                  |  136         |   185          |           176                     |                                    |
 **BRAMs used**                  |  2         |   4          |  4                              | 
 |**DSP used**|0|0|0|