# What is Dataflow?
Dataflow is one of the most powerful techniques in Vitis HLS for improving the throughput of your FPGA designs. Normally, when you write a series of functions or loops in C, each function call waits for the previous one to complete before starting. This means your design will finish processing all data in one stage before moving on to the next, underutilizing the FPGA’s ability to perform different operations in parallel.

Dataflow changes this by allowing different functions and loops in your top-level function to execute concurrently. This means that as soon as a piece of data finishes one stage, it can immediately begin the next stage while the previous stage starts processing new data. In practice, this allows multiple stages of your algorithm to remain active simultaneously, letting your design handle new data each cycle if there are no limitations, significantly improving throughput.

## Code examples
Here is a simple example where we first add two arrays and then multiply the result by 2:

```cpp
void add_arrays(int a[256], int b[256], int c[256]) {
    for (int i = 0; i < 256; i++) {
        c[i] = a[i] + b[i];
    }
}

void multiply_array(int c[256], int d[256]) {
    for (int i = 0; i < 256; i++) {
        d[i] = c[i] * 2;
    }
}

void top_function(int a[256], int b[256], int d[256]) {
    int c[256];
    add_arrays(a, b, c);
    multiply_array(c, d);
}
```

Using the DATAFLOW pragma, you can allow add_arrays and multiply_array to execute concurrently, processing and multiplying data in a streaming pipeline:

```cpp
void top_function(int a[256], int b[256], int d[256]) {
#pragma HLS DATAFLOW
    int c[256];
    add_arrays(a, b, c);
    multiply_array(c, d);
}
```
| metric          | Without Dataflow | With Dataflow |
| --------------- | ---------------- | ------------- |
| Latency(Cycles) | 520              | 518           |
| LUTs            | 236              | 184           |
| FFs             | 90               | 81            |
| BRAMs           | 1                | 1             |
| DSPs            | 0                | 0             |

With this modification, not only will the design be more efficient, but most importantly, spend less resources.
## Why Dataflow Matters
FPGAs are designed to perform multiple operations simultaneously, but unless you explicitly tell Vitis HLS to use dataflow, your top-level functions will execute sequentially, underutilizing the device’s parallelism. Dataflow allows you to structure your design so that independent or pipelined stages can operate concurrently, keeping all parts of your FPGA busy and increasing the data processing throughput of your design.

## How to Use Dataflow in Vitis
To use dataflow in your design, place the following pragma before the block containing your pipeline stages:

```cpp
#pragma HLS DATAFLOW
```
This tells Vitis HLS to attempt to schedule the functions or loops within the scope of the pragma to run concurrently, inserting FIFOs between stages to handle data streaming. It is important to ensure that each stage is pipelined or unrolled appropriately and that intermediate variables between stages are arrays or streams, not scalars, to enable effective data streaming.


