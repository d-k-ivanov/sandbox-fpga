# Problems in Loops – Underutilization of Hardware Due to Separate Loops
In FPGA designs using Vitis HLS, it is common to write separate loops for different operations on the same dataset. However, when these loops are executed independently, each loop incurs control overhead for initialization and exit, leading to extra cycles that reduce throughput. Additionally, separate loops cannot be pipelined together, leaving the FPGA’s computational resources underutilized between loops, especially when both loops could operate on the same data in a single pass.



## Example
Consider two loops performing separate operations on the same input array:

```cpp
void process_data(int a[256], int b[256], int c[256]) {
    for (int i = 0; i < 256; i++) {
        b[i] = a[i] * 2;
    }
    for (int i = 0; i < 256; i++) {
        c[i] = a[i] + 3;
    }
}
```
In this example, the first loop doubles each element in a and stores it in b, while the second loop adds 3 to each element in a and stores it in c. Each loop runs sequentially, incurring initialization and exit cycles, and preventing pipelining across both loops. The FPGA resources may remain idle between loops, and the design cannot overlap memory accesses and computations across these operations.

## The Solution
You can use loop merging to combine these separate loops into a single loop, reducing control overhead and enabling pipelining across both operations in the same loop. Vitis HLS provides the #pragma HLS LOOP_MERGE directive to assist with merging when multiple loops are adjacent and compatible.

```cpp
void process_data_merged(int a[256], int b[256], int c[256]) {
#pragma HLS LOOP_MERGE
    for (int i = 0; i < 256; i++) {
        b[i] = a[i] * 2;
    }
    for (int i = 0; i < 256; i++) {
        c[i] = a[i] + 3;
    }

}
```

| metric          | Without Merging | With Merging |
| --------------- | --------------- | ------------ |
| Latency(Cycles) | 520             | 259          |
| LUTs            | 228             | 112          |
| FFs             | 91              | 64           |
| BRAMs           | 0               | 0            |
| DSPs            | 0               | 0            |

By merging the loops, Vitis HLS transforms the two loops into a single loop with 256 iterations, removing the redundant initialization and exit cycles from the second loop. Pipelining can now be applied across both operations, ensuring the design produces one set of outputs (b[i] and c[i]) per cycle without stalls, maximizing hardware utilization and reducing overall execution time.

```
Note: Vitis will try to merge ALL loops in the same level to the directive and if it isn't possible to merge one due to dependencies the pragma will be ignored.  This can be avoided by moving the loops you dont want to merge to a sub function and turning inline off.
```
## Why Loop Merging Matters
Without loop merging, independent loops operating over the same data range add unnecessary control overhead, reduce the effectiveness of pipelining, and underutilize FPGA resources. Loop merging aligns multiple compatible operations into a single pass, reducing latency while improving throughput.

When loops operate over the same range and access the same arrays, merging them can reduce these inefficiencies, minimizing control overhead and enabling continuous pipelining across operations.
