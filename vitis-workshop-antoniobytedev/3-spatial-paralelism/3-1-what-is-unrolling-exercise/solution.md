# Solution
## factor of 2
```cpp
#include <hls_math.h>
#define N 256
void normalize(int in[N], float out[N]) {
    float sum_sq = 0.0;
    firstLoop:for (int i = 0; i < N; i++) {
        #pragma HLS PIPELINE off
        sum_sq += in[i] * in[i];
    }
    float norm = 1.0 / hls::sqrt(sum_sq);

    secondLoop:for (int i = 0; i < N; i++) {
        #pragma HLS unroll factor=2
        out[i] = in[i] * norm;
    }
    
}
```
## complete
```cpp
#include <hls_math.h>
#define N 256
void normalize(int in[N], float out[N]) {
    float sum_sq = 0.0;
    firstLoop:for (int i = 0; i < N; i++) {
        #pragma HLS PIPELINE off
        sum_sq += in[i] * in[i];
    }
    float norm = 1.0 / hls::sqrt(sum_sq);

    secondLoop:for (int i = 0; i < N; i++) {
        #pragma HLS unroll 
        out[i] = in[i] * norm;
    }
    
}
```
The best option out of the 3 is unrolling by a factor of 2. This allows us to duplicate the throughput without having reached the point of diminishing returns. This means that duplicating the area doubles our throughput.
# Finished table
| Metric                        | **No unroll** | **Partial unroll(factor=2)** | **Complete unroll** |
| ----------------------------- | ---------------------- | ------------------------------- | ---------------------------------- |
| **Latency in second loop (cycles)**    |            268            |                 129                |        0                            |
| **LUTs Used**                 |    729                |                          887      |      5634                                 |
| **FFs Used**                  |        822            |  1132                                |        1470                         |
| **DSPs Used**                 |       8               |                         11      |                             11       |
|**BRAMs Used**|0|0|0

