# What is Unrolling?
Unrolling is an important technique in Vitis HLS for making your FPGA designs faster by increasing parallelism. In C, loops typically execute one iteration at a time, reusing the same hardware resources for each iteration. This means your design processes only one element per cycle, which underutilizes the FPGA’s potential for parallel execution.

Unrolling changes this by allowing multiple iterations of the loop to be executed in parallel. Instead of waiting for one iteration to complete before starting the next, Vitis HLS replicates the hardware for each unrolled iteration, allowing your design to process multiple pieces of data at the same time and reducing the total execution time of the loop.

## Code Examples
Here is a simple example of multiplying each element of an array by 4:

```cpp
void multiply_array(int a[256], int c[256]) {
    for (int i = 0; i < 256; i++) {
        c[i] = a[i] * 4;
    }
}
```
In this version, the loop executes one iteration per cycle, requiring 256 cycles to process the entire array.

Using unrolling, you can instruct Vitis HLS to execute multiple iterations of the loop in parallel. For example, by unrolling the loop with a factor of 2, the design will process 2 elements per cycle, reducing the total execution time to 128 cycles instead of 256:

```cpp
void multiply_array_unroll(int a[256], int c[256]) {
    for (int i = 0; i < 256; i++) {
#pragma HLS UNROLL factor=2
        c[i] = a[i] * 4;
    }
}
```

Unrolling can also be applied fully, allowing the loop to execute all iterations simultaneously in a single clock cycle. This is done using the #pragma HLS UNROLL directive without specifying a factor:

```cpp
void multiply_array_full_unroll(int a[256], int c[256]) {
    for (int i = 0; i < 256; i++) {
        #pragma HLS UNROLL
        c[i] = a[i] * 4;
    }
}
```
By doing this vitis will replicate hardware so that all loop iterations can be executed in parallel. However, in this example,
we are limited by the number of memory ports so a complete unroll is meaningless. This will be explained further in the memory section.

| metric | rolled | unrolled |complete unroll|
| ------ | ------ | -------- |---------------|
| Cycles | 258    | 130      |128            |
| LUTs   | 70     | 56       |4751           |
| FFs    | 20     | 29       |129            |
| BRAMs  | 0      | 0        |0              |
| DSPs   | 0      | 0        |0              |


## Why Unrolling Matters
Unrolling allows your design to leverage the FPGA’s ability to execute many operations simultaneously, dramatically reducing execution time. By unrolling loops, you can match the parallelism of your algorithm to the available FPGA resources, increasing throughput and making your design capable of handling high-data-rate applications.

While unrolling improves speed, it also increases the use of hardware resources. Each unrolled iteration needs its own hardware resources, so using high unroll factors or full unrolling may exceed the available FPGA resources if not managed carefully.

## How to Use Unrolling in Vitis
To unroll a loop in Vitis HLS, place the following directive inside your loop:

```cpp
#pragma HLS UNROLL factor=4
```
This will unroll the loop with a factor of 4, executing 4 iterations in parallel per clock cycle. You can adjust the factor to control the trade-off between speed and hardware usage depending on your design’s constraints.

If you want to unroll the loop fully, allowing all iterations to execute in parallel, use:

```cpp
#pragma HLS UNROLL
```
This instructs Vitis HLS to replicate the loop body for all iterations and complete the entire loop in a single cycle, provided your design has sufficient resources to support this level of parallelism.

```
Note: To unroll a loop completely it can't have a variable bound.
```

Unrolling is a powerful optimization tool that helps you tune your design for maximum throughput, but it should be used carefully to ensure that your FPGA resources and memory bandwidth can support the required parallel operations. By strategically applying partial or complete unrolling, you can significantly improve your design's performance while balancing resource utilization to fit your specific application needs.


