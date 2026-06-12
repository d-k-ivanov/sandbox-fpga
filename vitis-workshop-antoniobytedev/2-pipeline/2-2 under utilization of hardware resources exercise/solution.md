# Solution

```cpp
void multiple_memory_access(int a[256], int result[128]) {

    for (int i = 0; i < 128; i++) {
        #pragma HLS PIPELINE II=2
        result[i] = a[2 * i] + a[2 * i + 1] + a[i];

    }
}
```
The minimum achievable initiation interval (II) in this case is 2, due to the dual-port limitation of the memory. Since each iteration requires three separate memory accesses to the same array, and the memory can only serve two accesses per clock cycle, it is not possible to sustain an initiation interval of 1 without array partitioning. Therefore, II = 2 represents the lowest feasible value under the given memory constraints.

Despite not being able to achieve II=1 due to lack of memory ports, we were able to increase throughput by a factor of 2. This is important, because even if it's impossible to achieve II=1 you should always consider if it's possible to pipeline when designing an FPGA.
## Finished table
| Metric                        | **Without Pipelining** | **With `#pragma HLS PIPELINE II=2`** |
| ----------------------------- | ---------------------- | ------------------------------- |
 **Total Latency (cycles)**    |             513|                        259        
| **LUTs Used**                 |    142          |                          167    |
| **FFs Used**                  |           93              |               124            |
| **DSPs Used**                 |  0                |                0     |
| **BRAMs Used**                |   0                   |   0                              |


