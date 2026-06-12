# Solution
1.This generates an architecture that automatically pipelines all loops.

2.By loop merging we increase throughput by a factor of 4, while not increasing LUTs and FFs by much but doubling DSPs. This is a fantastic tradeoff as we receive much more than we invested.
```cpp
#define N 256

typedef struct {
    float real;
    float imag;
} complex_t;

void fft(complex_t x[N], complex_t X[N]) {

    #pragma HLS LOOP_MERGE
    complex_t a[N];

copy_loop:
    for(int i = 0; i < N; i++) {
        a[i] = x[i];     // Copy step
    }

init_loop:
    for(int i = 0; i < N; i++) {
        // Initialize values in a deterministic and independent way
        a[i].real = a[i].real * 0.5f + 1.0f;
        a[i].imag = a[i].imag * 0.25f;
    }

transform_loop:
    for(int i = 0; i < N; i++) {
        // Arbitrary transformation, no dependency on neighbors
        float temp = a[i].real + a[i].imag;
        a[i].real = temp * 0.8f;
        a[i].imag = temp * 1.2f;
    }

write_loop:
    for(int i = 0; i < N; i++) {
        X[i] = a[i];
    }
}

```

3. By doing a fully iterative throughput increases exponentially, but we can cut the number of FFs and LUTs by half.
```cpp
#define N 256

typedef struct {
    float real;
    float imag;
} complex_t;

void fft(complex_t x[N], complex_t X[N]) {

    complex_t a[N];
#pragma HLS LOOP_MERGE
copy_loop:
    for(int i = 0; i < N; i++) {
        #pragma HLS PIPELINE off
        a[i] = x[i];     // Copy step
    }

init_loop:
    for(int i = 0; i < N; i++) {
         #pragma HLS PIPELINE off
        // Initialize values in a deterministic and independent way
        a[i].real = a[i].real * 0.5f + 1.0f;
        a[i].imag = a[i].imag * 0.25f;
    }

transform_loop:
    for(int i = 0; i < N; i++) {
         #pragma HLS PIPELINE off
        // Arbitrary transformation, no dependency on neighbors
        float temp = a[i].real + a[i].imag;
        a[i].real = temp * 0.8f;
        a[i].imag = temp * 1.2f;
    }

write_loop:
    for(int i = 0; i < N; i++) {
         #pragma HLS PIPELINE off
        X[i] = a[i];
    }
}

```

4. Throughput doesn't increase because unrolling inside the loops prevents them from being merged, thus achieving the same throughput as baseline with loops merged but having a significant increase in area. The only way to fix this is by merging loops manually.
```cpp
#define N 256

typedef struct {
    float real;
    float imag;
} complex_t;

void datapath1(complex_t x[N], complex_t X[N]) {

    complex_t a[N];
    #pragma HLS ARRAY_PARTITION variable=x dim=1 type=cyclic factor=2
    #pragma HLS ARRAY_PARTITION variable=X dim=1 type=cyclic factor=2
#pragma HLS LOOP_MERGE
copy_loop:
    for(int i = 0; i < N; i++) {
        #pragma HLS UNROLL factor=4
        a[i] = x[i];     // Copy step
    }

init_loop:
    for(int i = 0; i < N; i++) {
     #pragma HLS UNROLL factor=4
        // Initialize values in a deterministic and independent way
        a[i].real = a[i].real * 0.5f + 1.0f;
        a[i].imag = a[i].imag * 0.25f;
    }

transform_loop:
    for(int i = 0; i < N; i++) {
      #pragma HLS UNROLL factor=4
        // Arbitrary transformation, no dependency on neighbors
        float temp = a[i].real + a[i].imag;
        a[i].real = temp * 0.8f;
        a[i].imag = temp * 1.2f;
    }

write_loop:
    for(int i = 0; i < N; i++) {
       #pragma HLS UNROLL factor=4
        X[i] = a[i];
    }

}

```

5.
 
```
| metric          | Baseline | Loop Merge |Fully Iterative | Latency Reduction(Parallelization) |
| --------------- | ---------|------------|-----------------| ---------------------------------- |
| Latency(Cycles) |1059   |        277        |      5377      |      291                             |
| LUTs            |  1241     |   1079             |    686        |     3933                              |
| FFs             |   1217       |  1425              |     691       |    4483                               |
| DSPs            |     8     |         16       |     8       |         32                          |
| BRAMs           |      4    |        0        |      0      |          16                         |

Here by far the most efficient design is Loop Merge baseline. Not only does it achieve the highest throughput it does so while having the second lowest resource usage on this table.  However, dependending on your objectives you may prefer the fully iterative or the latency reduction versions.
