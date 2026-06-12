# Problems in Pipelining – Minimum II Constrained by Available Memory Ports
In FPGA designs using Vitis HLS, on-chip BRAM typically offers two ports, allowing two simultaneous memory accesses either reads, writes, or both in a single clock cycle. When loops in your design require more memory accesses per iteration than the number of available ports, this imposes a hard limit on how frequently new iterations can begin. Specifically, it increases the minimum achievable initiation interval (II), meaning that even if the computational logic could support processing data every cycle, the memory subsystem becomes a bottleneck.

## Example
Consider the following loop, which processes trios of elements from an array and stores their sum:

```cpp
void accumulate_shifted(int a[256], int result[256]) {
    int temp = 0;

    for (int i = 0; i < 256-2; i++) {
        #pragma HLS PIPELINE off

        int x = a[i];               
        int y = a[(i + 1)]; 
        int z = a[(i + 2)];  

        temp = x + y + z;

        result[i] = temp;
    }
}
```
Each iteration requires three reads from the array a. Because BRAM has two read ports, it is not possible to achieve II=1.

## The Solution
Despite not being able to achieve II=1, vitis can schedule data so that a new iteration can start every 2 or more cycles. Vitis will do this automatically when II=1 can't be achieved, but to get a specific number of iterations it's important to specify it, for example by writing II=2(new iteration every 2 cycles).

```cpp
void accumulate_shifted(int a[256], int result[256]) {
    int temp = 0;

    for (int i = 0; i < 256-2; i++) {
        #pragma HLS PIPELINE II=2

        int x = a[i];               
        int y = a[(i + 1)]; 
        int z = a[(i + 2)];  

        temp = x + y + z;

        result[i] = temp;
    }
}
```
| Metric                        | **Without Pipelining** | **With `#pragma HLS PIPELINE II=2`** |
| ----------------------------- | ---------------------- | ------------------------------- |
 **Total Latency (cycles)**    |                1017       |                511                
| **LUTs Used**                 |    156                    | 184                               |
| **FFs Used**                  |        101               |     135                            |
| **DSPs Used**                 |      0                  |         0                        |
| **BRAMs Used**                |       0                 |          0                       |

## Why Memory Port Count Affects II
Despite not being able to achieve II=1 due to lack of memory ports it is important to note that throughput is still much higher with a low II than with no pipeline at all, which goes to show how powerful this pragma really is.




