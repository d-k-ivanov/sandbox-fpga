# SOLUTION

```cpp
#define N 256

void cyclic_partition(int A[N], int B[N], int C[N]) {
int bufferA[N];
int bufferB[N];
for(int i=0;i<N;i++)
{
    bufferA[i] = A[i];
    bufferB[i] = B[i];
}
#pragma HLS ARRAY_PARTITION variable=bufferA type=cyclic factor=4
#pragma HLS ARRAY_PARTITION variable=bufferB type=cyclic factor=4
#pragma HLS ARRAY_PARTITION variable=C type=cyclic factor=4

    for (int i = 0; i < N; i++) {
        #pragma HLS PIPELINE II=1
        #pragma HLS UNROLL factor=4
        C[i] = bufferA[i] + bufferB[i];
    }
}

//////////////////////////////////////////////////////////////
void block_partition(int A[N], int B[N], int C[N]) {
int bufferA[N];
int bufferB[N];
for(int i=0;i<N;i++)
{
    bufferA[i] = A[i];
    bufferB[i] = B[i];
}
#pragma HLS ARRAY_PARTITION variable=bufferA type=block factor=4
#pragma HLS ARRAY_PARTITION variable=bufferB type=block factor=4
#pragma HLS ARRAY_PARTITION variable=C type=block factor=4

    for (int i = 0; i < N; i++) {
        #pragma HLS PIPELINE II=1
        #pragma HLS UNROLL factor=4
        C[i] = bufferA[i] + bufferB[i];
    }
}
//////////////////////////////////////////////////////////////

void complete_partition(int A[N], int B[N], int C[N]) {
int bufferA[N];
int bufferB[N];
for(int i=0;i<N;i++)
{
    bufferA[i] = A[i];
    bufferB[i] = B[i];
}
#pragma HLS ARRAY_PARTITION variable=bufferA type=complete
#pragma HLS ARRAY_PARTITION variable=bufferB type=complete 
#pragma HLS ARRAY_PARTITION variable=C type=complete

    for (int i = 0; i < N; i++) {
        #pragma HLS PIPELINE II=1
        #pragma HLS UNROLL factor=4
        C[i] = bufferA[i] + bufferB[i];
    }
}
```
As you can see in the table because we only unrolled by a factor of 4, partitioning by a cyclic factor of 4 is the best option for performance in regards to resources used. Using block partitioning doesn't help us at all, since the memory isn't partitioned in a way the hardware can take advantage from it. Complete partitioning, on the other hand, let's us get the same number of cycles as with cyclic partitioning but with exponentially more resources.

## Complete table

# Finished table
| **Metric**                      | **Without partition** | **Cyclic factor=4** | **Block factor =4** | **Complete** 
|:-------------------------:|:---------------------:|:-------------------:|:-------------------:|:------------:
| **Total Latency(cycles)** |      392           |    328               |    392                |           327|      |      |      |      |      |
| **LUTs used**             | 412                    |   582                |      1228               |        4479      |      |      |      |      |      |
| **FFs used**              |    140             |        180             |  196                 |              24613|      |      |      |      |      |
| **DSPs used**             |     0               |   0                  |     0             |         0    |   0   |      |      |      |      |
| **BRAMs used**             |      4              |       8              |    16              |          0   |      |      |      |      |      |




