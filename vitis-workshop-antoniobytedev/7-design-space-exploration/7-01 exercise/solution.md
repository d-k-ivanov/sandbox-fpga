# Solution
1. This generates an architecture that applies automatically the pipeline pragma and unrolls the conv_inner loop by a factor of 5.

2. 
```cpp
#define N 32          // Length of input signal
#define K 5           // Length of kernel/filter
#define OUT_LEN (N+K-1)

void convolution_1d(int input[N], int kernel[K], int output[OUT_LEN]) {

    // Initialize output
    init_loop:
    for (int i = 0; i < OUT_LEN; i++) {
        #pragma HLS PIPELINE off
        output[i] = 0;
    }

    // Convolution accumulation
    conv_outer:
    for (int i = 0; i < N; i++) {
        conv_inner:
        for (int j = 0; j < K; j++) {
            #pragma HLS PIPELINE off
            output[i + j] += input[i] * kernel[j];
        }
    }
}
```
The Pipeline off directive will stop pipelining and unrolling, which reduces resource usage and throughput by a factor of 3.
3.

```cpp
void convolution_1d(int input[N], int kernel[K], int output[OUT_LEN]) {

    #pragma HLS ARRAY_PARTITION variable=input dim=1 type=cyclic factor=2
    #pragma HLS ARRAY_PARTITION variable=kernel dim=1 type=cyclic factor=2
    #pragma HLS ARRAY_PARTITION variable=output dim=1 type=cyclic factor=2
    // Initialize output
    init_loop:
    for (int i = 0; i < OUT_LEN; i++) {
        //#pragma HLS PIPELINE off
        output[i] = 0;
    }

    // Convolution accumulation
    conv_outer:
    for (int i = 0; i < N; i++) {
        conv_inner:
        #pragma HLS PIPELINE II=1
        for (int j = 0; j < K; j++) {
            output[i + j] += input[i] * kernel[j];
        }
    }
}
```
Because the inner loop is unrolled completely, to reduce latency by a factor of 4 we only need to partition all variables by a cyclic factor of 2, adding 4 new ports and thus increasing throughput by a factor of 4.

4.

| metric          | Baseline | Fully Iterative | Latency Reduction(Parallelization) |
| --------------- | -------- | --------------- | ---------------------------------- |
| Latency(Cycles) | 206      | 774             | 77                                 |
| LUTs            | 711      | 246             | 1544                               |
| FFs             | 584      | 172             | 1320                               |
| DSPs            | 15       | 3               | 60                                 |
| BRAMs           | 0        | 0               | 0                                  |


The most efficient one is the baseline, because it has the most balance between area and throughput. However, dependending on your objectives you may prefer the fully iterative or the latency reduction versions.