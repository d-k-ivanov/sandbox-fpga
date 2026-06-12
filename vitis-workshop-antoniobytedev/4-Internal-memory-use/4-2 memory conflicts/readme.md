# Problems in Memory – Underutilization of Hardware due to lack of memory ports
In FPGA designs using Vitis HLS, on-chip BRAM typically provides only two ports, allowing two simultaneous reads or writes per cycle. However, when your design requires accessing more than two data elements per cycle, the BRAM’s limited port availability can become a bottleneck. Even if your computation could handle processing more data in parallel, the memory architecture limits the design’s ability to feed data fast enough, leaving your arithmetic units idle and underutilizing FPGA resources.

## Example
```cpp
void sum_quads(int a[256], int result[256]) {
    for (int i = 0; i < 256; i++) {
        #pragma HLS PIPELINE II=1
        #pragma HLS UNROLL factor=4;
        result[i] = a[i]*4;
    }
}
```
Each iteration requires reading four different elements from the array a to compute the sum. Since BRAM only allows two reads per cycle, Vitis HLS cannot fetch all four required elements in a single cycle. This forces the design to spread the reads across multiple cycles, causing the adder to wait for data and remain idle during some cycles, limiting the throughput of the loop. Even if the computation itself could complete in one cycle, the memory bandwidth limitation extends the effective initiation interval, underutilizing the potential of your FPGA.

## The Solution
To address this limitation, you can use array partitioning to split the array into multiple smaller memories, allowing parallel accesses to different memory banks within the same cycle. By partitioning the array cyclically with a factor of 4, each bank will store every fourth element, enabling simultaneous access to the four required elements in one cycle.

```cpp
void sum_quads_partitioned(int a[256], int result[256]) {
#pragma HLS ARRAY_PARTITION variable=a type=cyclic factor=4
#pragma HLS ARRAY_PARTITION variable=result type=cyclic factor=4
    for (int i = 0; i < 256; i++) {
        #pragma HLS PIPELINE II=1
        #pragma HLS UNROLL factor=4
        result[i] = a[i]*4
    }
}l
```
Doing the c synthesis will show these results:

|        | no partition | cyclic(factor=4) |
| ------ | ------------ | ---------------- |
| Cycles | 131          | 66               |
| LUT    | 156          | 56               |
| FF     | 114          | 19               |
| BRAMs  | 0            | 0                |
| DSP    | 0            | 0                |

By partitioning a cyclically with a factor of 4, Vitis HLS splits the original array into 4 separate memories, each storing elements like a[0], a[4], a[8], ..., a[1], a[5], a[9], ..., and so on. Since each of these new memories has its own ports, the design can now read all four required elements simultaneously in a single cycle.

Combined with pipelining, this ensures:

All four required data reads occur in the same cycle.

The adder receives all its inputs without delay.

A new sum is produced every cycle, achieving II = 1.

The FPGA’s BRAM ports and arithmetic units are fully utilized, maximizing throughput.

## Why Array Partitioning Matters
Without array partitioning, memory access limitations often become the bottleneck in FPGA designs, leaving your computational resources underutilized. Array partitioning allows you to align your memory architecture with the parallelism of your computation, ensuring that data can be fed to the logic at the rate it can process. This enables you to achieve the performance gains you expect from pipelining and unrolling while making effective use of the FPGA’s resources.

# Other types of array partitioning

Depending on your necessities you may need to use one of the following types:

## Block Partitioning
Block partitioning divides the array into contiguous blocks stored in separate memory banks.

```cpp
#pragma HLS ARRAY_PARTITION variable=a block factor=4
```
Using block partitioning with a factor of 4 will split a into 4 blocks: the first storing a[0] to a[63], the second a[64] to a[127], and so on. This method is useful when your computation accesses data in a way that aligns with the block structure, such as when processing large, independent data chunks. However, for operations requiring simultaneous access to adjacent elements, block partitioning may not fully resolve access bottlenecks because adjacent data may still reside in the same block.

## Complete Partitioning
Complete partitioning stores each element of the array in a separate register or distributed RAM.

```cpp
#pragma HLS ARRAY_PARTITION variable=a complete
```
This allows full parallel access to every element, eliminating all memory access bottlenecks and achieving maximum throughput. However, it uses significant FPGA resources, as it requires as many registers or distributed RAM elements as the size of the array. This method should be used only when maximum performance is required and the FPGA has sufficient resources to support full parallelism.
