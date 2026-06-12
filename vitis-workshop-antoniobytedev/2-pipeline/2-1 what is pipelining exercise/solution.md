# Solution
```cpp
#define N 1024
void offset(float in[N], float out[N]) {
    for (int i = 0; i < N; i++) {
        #pragma HLS PIPELINE II=1
        out[i] = in[i] + 10.0f;
    }
}
```
By modestly increasing the number of LUTs and FFs we were able to increase the throughput by a factor of 8, showing the real power of pipeline.

## Finished table
| Metric                        | **Without Pipelining** | **With `#pragma HLS PIPELINE`** |
| ----------------------------- | ---------------------- | ------------------------------- |
 **Total Latency (cycles)**    |              8103          |        1032                         
| **LUTs Used**                 |    290              |                          309       |
| **FFs Used**                  |      300                   |    369                             |
| **DSPs Used**                 |  2                   |     2                            |
| **BRAMs Used**                |   0                   |   0                              |

