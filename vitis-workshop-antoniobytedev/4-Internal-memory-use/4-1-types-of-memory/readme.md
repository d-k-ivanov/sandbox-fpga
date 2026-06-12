# Basic types
## Scalar variables
A scalar variable is any non array or pointer variable.

For example: 
```cpp
int sum = 0;
bool done = false;
ap_uint<8> gain = 3;
```
These variables are stored in **flip-flops**. The number of flip flops used depends on the type of variable.

| C++ Type     | Bits | Synthesized as        |
| ------------ | ---- | --------------------- |
| `bool`       | 1    | 1 flip-flop       |
| `int`        | 32   | 32 flip-flops |
| `ap_uint<8>` | 8    | 8 flip-flops |

Flip-flops are the most important type of memory, as they have no access latency and enable pipeling and unrolling by breaking combinational dependencies.


## Local memory
 Local memory mostly consists of Arrays declared inside a function or passed through the top function. These don’t interface with external memory (like DRAM via AXI); instead, they’re implemented using on-chip memory blocks like:

BRAM: Block RAM

URAM: Ultra RAM (for UltraScale+ FPGAs)

These memories live entirely on the FPGA fabric, giving you low-latency, high-bandwidth internal storage.

### Differences between BRAM and URAM
| Feature        | BRAM                      | URAM                       |
| -------------- | ------------------------- | -------------------------- |
| Size per block | \~36 Kbits                | \~288 Kbits                |
| Latency        | 1 clock cycle             | 2–3 clock cycles           |
| Max bandwidth  | 2 accesses per cycle    | 2 accesses per cycle  |
| Suitable for   | Medium buffers (KB range) | Large buffers (MB range)   |
| FPGA support   | Most FPGAs                | Only UltraScale+ and newer |

As we will be working with mostly small arrays, we will focus on BRAM for this tutorial.

When you use an array as an argument to the top-level function, Vitis HLS assumes one of the following:

* Memory is off-chip and Vitis HLS synthesizes M_AXI ports on the interface to access the memory as the default for the Vitis Kernel flow.

* Memory is standard block RAM with a latency of 1 as the default behavior in the Vivado IP flow. The data is ready one clock cycle after the address is supplied.

### Creating local memory in Vitis hls

```cpp
void example() {
    int buffer[256];
    ...
}
```

In this code vitis HLS will map buffer to a BRAM memory.

## External memory 
External memory refers to any memory resource not on the FPGA itself. — typically:

* DDR memory (attached to the Processing System or PL)

* LPDDR, HBM, or external DRAM
 
 This memory is not accessed directly using cpp code, being accessed through interfaces like AXI instead.

 To declare external memory we need to create arguments in the top function and use AXI pragmas to work with them.

 ```cpp
void top_function(int[256] in, int[256] out)
{
    #pragma HLS INTERFACE m_axi port=in  bundle=gmem
    #pragma HLS INTERFACE m_axi port=out bundle=gmem
    ...
}
```



| Memory Type    | On-chip | Access Speed | Size                     | Accessed via  |
| -------------- | ------- | ------------ | ------------------------ | ------------- |
|Flip-flop|yes|Fastest|Very small(1 bit)|Scalar variables|
| BRAM           | yes       | Fast         | Small (KBs)              | Local arrays  |
| URAM           | yes       | Medium       | Larger (hundreds of KBs) | Local arrays  |
| DDR (external) | no      | Slow         | Large (GBs)              | `m_axi` ports |


