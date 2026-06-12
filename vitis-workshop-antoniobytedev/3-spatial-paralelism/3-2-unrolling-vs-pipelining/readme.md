# Comparing Unrolling and Pipelining in Vitis HLS
Unrolling and pipelining are two of the most important techniques for making your FPGA designs faster in Vitis HLS. Both aim to increase throughput and reduce latency, but they do so in different ways and have different impacts on resource usage, latency, and how your design uses FPGA parallelism.


# Pipelining Example
Consider a loop that multiplies each element of an array by 4.

Without any optimization, the loop will process one element per cycle, requiring 256 cycles to process 256 elements.

Using pipelining, you can allow the loop to start a new iteration every cycle even if the multiplication takes multiple cycles internally:

```cpp
void multiply_pipeline(int a[256], int c[256]) {
    rolled:for (int i = 0; i < 256; i++) {
        #pragma HLS PIPELINE II=1
        c[i] = a[i] * 4;
    }
}
```
With this approach, the design will take a few cycles to produce the first output, but after that, it will produce one output per cycle, completing in approximately 256 cycles while keeping the hardware resource usage low.

## Unrolling example
Using unrolling, you can reduce the total number of cycles by processing multiple elements in parallel per cycle:

```cpp
void multiply_unroll(int a[256], int c[256]) {
    unrolled:for (int i = 0; i < 256; i++) {
#pragma HLS UNROLL factor=2
#pragma HLS PIPELINE II=1
        c[i] = a[i] * 4;
    }
}
```
| metric | rolled | unrolled |
| ------ | ------ | -------- |
| Cycles | 258    | 130      |
| LUTs   | 70     | 56       |
| FFs    | 20     | 29       |
| BRAMs  | 0      | 0        |
| DSPs   | 0      | 0        |

Here, the design processes two elements per cycle, reducing the total execution time to 128 cycles, but requiring two multipliers and sufficient memory bandwidth to handle four reads and writes per cycle.

## Key Differences
Pipelining increases throughput by allowing new data to enter the computation every cycle while reusing the same hardware across loop iterations. It is efficient in terms of hardware usage and is effective in reducing the effective latency per data element when the operation has a long delay.

Unrolling increases throughput by executing multiple loop iterations in parallel using duplicated hardware, reducing the total number of cycles needed to complete the entire loop. It is effective in reducing total loop latency, but it requires additional resources proportional to the unroll factor.

## When to Use Each
Use pipelining when your design needs to handle continuous data streams efficiently and when your operations take multiple cycles to complete internally. Pipelining is also preferable when FPGA resources are limited, as it reuses the same hardware across iterations.

Use unrolling when you need to reduce the overall execution time of a loop and your FPGA has enough resources and memory bandwidth to support parallel operations. Partial unrolling with controlled factors is often used to find a balance between performance and hardware usage.

In many practical designs, pipelining and unrolling are used together to achieve the desired performance. For example, you may pipeline a loop to process data every cycle while partially unrolling the loop to process multiple elements per cycle within each pipeline stage, optimizing both throughput and hardware utilization.

## Summary
Pipelining and unrolling are both essential tools in Vitis HLS for creating high-performance FPGA designs. Pipelining allows overlapping of operations across iterations to improve data processing rates without significantly increasing resource usage. Unrolling reduces the total execution time of a loop by executing iterations in parallel but requires more hardware resources. By understanding the strengths and limitations of each technique, you can apply them effectively to match your application's performance needs while respecting the resource constraints of your FPGA design.