# Solution
```cpp
#define N 128

void pipeline_off(int A[N], int B[N]) {
    for (int i = 0; i < N - 2; i++) {
        #pragma HLS PIPELINE off
        int sum = A[i] + A[i + 1] + A[i + 2];
        B[i] = sum;
    }
}

void partitioned(int A[N], int B[N]) {
    #pragma HLS ARRAY_PARTITION variable=A type=cyclic factor=2
    for (int i = 0; i < N - 2; i++) {
        #pragma HLS PIPELINE II=1
        int sum = A[i] + A[i + 1] + A[i + 2];
        B[i] = sum;
    }
}
```
Partitioning memory A by a factor of 2 allows us to reach double throughput, but also doubles LUTs used. Removing pipeline leads us to double the latency but reduces the number of resources used. The best architecture of the three depends on what our objective is (maximizing throughput, minimizing area or finding a balance of both).
## Finished Table
| Metric                        | **Without Partitioning** | **With Partitioning** |**Without Pipeline**
| ----------------------------- | ---------------------- | ------------------------------- | ------------------------------- | 
| **Total Latency (cycles)**    |           255            | 130  |                 505             |                                    |
| **LUTs Used**                 |   181        |      302      |         153                        |                                    |
| **FFs Used**                  | 131          |    133         |             97                    |                                    |
 **BRAMs used**                  | 0          |     0        |               0                  | 
 |**DSP used**|0|0|0|
