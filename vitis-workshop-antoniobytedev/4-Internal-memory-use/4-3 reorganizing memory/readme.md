# Problems in Memory – Underutilization of Bandwidth Due to Narrow Accesses
The ARRAY_RESHAPE pragma reorganizes an array by grouping and concatenating multiple elements into wider elements, effectively increasing their bit-width. This process reduces the total number of block RAMs used while still allowing parallel access to the data. By creating a new array with fewer, wider elements, you enable your design to access more data in a single clock cycle, improving memory bandwidth and making your FPGA design more efficient.

# Example
Consider a simple loop that increments each element of an 8-element char array by 1:
```cpp
void increment_array(char a[256], char out[256]) {
    for (int i = 0; i < 256; i++) {
        #pragma HLS UNROLL factor=8
        out[i] = a[i] + 1;
    }
}
```
In this example, each iteration accesses only one char (8 bits) per cycle. Even though the FPGA may support 32-bit or 64-bit accesses per cycle, the design only uses 8 bits, wasting bandwidth on each transfer and limiting the effective data throughput of your design.

## The Solution
You can use memory reorganization with the #pragma HLS ARRAY_RESHAPE directive to pack multiple narrow elements into a single wide memory word, aligning with your memory interface’s width. This allows your design to read or write multiple elements in a single cycle, improving bandwidth utilization and reducing latency.

Applying cyclic reshaping with a factor of 8 allows the FPGA to access 8 char elements (32 bits) per cycle:

```cpp
void increment_array_reshaped(char a[256], char out[256]) {
#pragma HLS ARRAY_RESHAPE variable=a factor=8 dim=1 type=cyclic
#pragma HLS ARRAY_RESHAPE variable=out factor=8 dim=1 type=cyclic

    for (int i = 0; i < 256; i++) {
        #pragma HLS UNROLL factor=8
        out[i] = a[i] + 1;
    }
}
```

|        | no reshaping | cyclic(factor=8) |
| ------ | ------------ | ---------------- |
| Cycles |   131        | 34              |
| LUT    |    265       | 176               |
| FF     |  96         | 18              |
| BRAMs  | 0            | 0                |
| DSP    | 0            | 0                |

By doing this the throughput increases significantly, without having to increase the area much.

## Why Memory Reshaping Matters
Without memory reshaping, FPGA designs accessing narrow data types waste available memory bandwidth, increasing execution latency even if loops are fully pipelined. By reshaping arrays, you align your memory structures with the physical memory interfaces of the FPGA, ensuring that each cycle performs meaningful data transfer that matches the bus width. This allows your design to maintain continuous pipelined execution while maximizing memory throughput and resource utilization.

## Types of Array Reshaping
Vitis HLS supports three reshaping styles:

Cyclic Reshape groups elements in a round-robin pattern across packed words, aligning with interleaved sequential access. For example, a[8] with factor=4 reshapes into two groups: [a0, a2, a4, a6] and [a1, a3, a5, a7].

```cpp
#pragma HLS ARRAY_RESHAPE variable=a factor=4 dim=1 type=cyclic
```
Block Reshape groups elements into contiguous blocks, which is ideal for tile-based processing or when accessing data in chunks. For the same a[8], block reshape with factor=4 groups [a0, a1, a2, a3] and [a4, a5, a6, a7].

```cpp
#pragma HLS ARRAY_RESHAPE variable=a factor=4 type=block
```
Complete Reshape packs all elements of the array into a single memory word, allowing all elements to be accessed in one cycle, which is useful for small arrays where full-width, one-cycle access is desired.

```cpp
#pragma HLS ARRAY_RESHAPE variable=a type=complete
```
## Reshape vs. Partition
While array reshaping packs multiple elements into wider words to maximize memory bandwidth on a single BRAM and save resources, array partitioning splits arrays into separate banks or registers to allow fully parallel independent accesses, supporting high-throughput parallel computation. Partitioning is better when using pipeline and reshape when focusing on unrolling.




