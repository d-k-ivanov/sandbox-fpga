# What is pipelining?
Pipelining is one of the most important techniques in Vitis HLS for making your designs faster. When you write a loop in C, each iteration normally waits for the previous one to finish before starting. This means that if the operations inside your loop take several clock cycles, your design will only process one piece of data every few cycles, which is slow for FPGA hardware that can handle much more.

Pipelining changes this by allowing the loop to start a new iteration before the previous iteration has completed. This means that multiple iterations are active in different stages of execution at the same time, allowing your design to process a new piece of data every clock cycle if there are no limitations.

## Code examples
Here is a simple example of adding two arrays:

```cpp
void add_arrays(int a[256], int b[256], int c[256]) {
    for (int i = 0; i < 256; i++) {
        /*because this loop has more than 64 iterations vitis will
        try to pipeline it automatically,
         so it's important to turn pipeline off to compare the results*/
        #pragma HLS PIPELINE off
        c[i] = a[i] + b[i];
    }
} 
```
In this version, each addition will wait for the previous one to finish before starting. If each addition takes 3 cycles, the total execution time will be around 768 cycles for 256 elements.


Using pipelining, you can allow the loop to start a new addition every cycle, even if the addition takes 3 cycles to complete:

```cpp
void add_arrays_pipeline(int a[256], int b[256], int c[256]) {
    for (int i = 0; i < 256; i++) {
        #pragma HLS PIPELINE II=1
        c[i] = a[i] + b[i];
    }
}
```

| Metric                        | **Without Pipelining** | **With `#pragma HLS PIPELINE`** |
| ----------------------------- | ---------------------- | ------------------------------- |
 **Total Latency (cycles)**    |              769          |             259                   
| **LUTs Used**                 |    102                    |              109                   |
| **FFs Used**                  |      54                  |             62                    |
| **DSPs Used**                 |      0                  |         0                        |
| **BRAMs Used**                |       0                 |          0                       |

With this modification, the design will still take 3 cycles to produce the first result, but after that, it will produce one result per cycle. The total execution time will be about 259 cycles instead of 768. These synthesis results show us that pipeline is crucial when looking for throughput, as it allows us to make a significant increase in it while minimally increasing resources.

## Why Pipelining Matters
FPGAs are capable of executing many operations in parallel, but unless you explicitly tell Vitis HLS to pipeline your loops, your code will behave like it does in software, executing operations one at a time. Pipelining helps you use the FPGA’s resources efficiently, keeping arithmetic units busy and increasing the processing speed of your design.

## How to Use Pipelining in Vitis 
To pipeline a loop, place the following code before your loop:

```cpp
#pragma HLS PIPELINE II=1
```
Where II is s the number of clock cycles between the start of one iteration of the loop and the start of the next. A lower II means higher throughput. An II of 1 means a new iteration starts every clock cycle, which is the best possible scenario.

 This tells Vitis to try to start a new loop iteration every clock cycle if there are no memory or dependency limitations. If your design has dependencies between loop iterations, you may not achieve II=1 automatically, but pipelining will still improve performance by overlapping iterations as much as possible.