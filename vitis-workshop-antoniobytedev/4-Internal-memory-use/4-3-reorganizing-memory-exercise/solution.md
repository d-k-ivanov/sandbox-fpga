

# Solution
```cpp
#define SIZE 256
void combine_arrays_reshaped(short a[SIZE], short b[SIZE], short c[SIZE], short out[SIZE]) {
#pragma HLS ARRAY_RESHAPE variable=a factor=4 dim=1 type=cyclic
#pragma HLS ARRAY_RESHAPE variable=b factor=4 dim=1 type=cyclic
#pragma HLS ARRAY_RESHAPE variable=c factor=4 dim=1 type=cyclic
#pragma HLS ARRAY_RESHAPE variable=out factor=4 dim=1 type=cyclic

    const short w1 = 2;
    const short w2 = 3;
    const short w3 = 4;

    for (int i = 0; i < SIZE; i++) {
        #pragma HLS UNROLL factor=8
        out[i] = a[i] * w1 + b[i] * w2 - c[i] * w3;
    }
}
```

To get the maximum throughput in regards to area we need to unroll by a factor of 8. This is because cyclic reshaping allows us 2 accesses to each element per cycle.

## Complete table
| Metric                        | **Without Unrolling** | **With Unrolling** 
| ----------------------------- | ---------------------- | ------------------------------- | 
| **Total Latency (cycles)**    |                   256     |        35                         |                                    |
| **LUTs Used**                 |                125        |                         496        |                                    |
| **FFs Used**                  |   78                     |                 397                |                                    |
|**BRAMs Used**|0|0|
|**DSP Used**|0|0|

