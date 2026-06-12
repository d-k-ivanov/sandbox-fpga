1. This architecture applies pipeline automatically in all loops. If we didn't have the pragma inline turned off it would also inline all functions.

2. By inlining not only do we increase throughput exponentially but also reduce area.
```cpp
#include <stdint.h>

#define N 64

// Stage 1: Normalize input
void normalize(int in[N], int out[N]) {
    #pragma HLS inline 
normalize_loop:
    for (int i = 0; i < N; i++) {
        out[i] = (in[i] > 100) ? 100 : in[i];
    }
}

// Stage 2: Greedy filter: keep only large values
void greedy_filter(int in[N], int out[N]) {
    #pragma HLS inline 
filter_loop:
    for (int i = 0; i < N; i++) {
        out[i] = (in[i] > 50) ? in[i] : 0;
    }
}

// Stage 3: Accumulate score
void accumulate(int in[N], int &result) {
    #pragma HLS inline 
    int sum = 0;
acc_loop:
    for (int i = 0; i < N; i++) {
        sum += in[i];
    }
    result = sum;
}

void greedy_dataflow_top(int input[N][N], int &output) {

    int norm_buf[N];
    int greedy_buf[N];
    for(int i=0;i<N;i++)
    {
        normalize(input[i], norm_buf);
        greedy_filter(norm_buf, greedy_buf);
        accumulate(greedy_buf, output);
    }
}
   

```

3. By turning pipeline off in all loops we reduce resource usage significantly but also increase latency by a lot.
```cpp
#include <stdint.h>

#define N 64

// Stage 1: Normalize input
void normalize(int in[N], int out[N]) {
    #pragma HLS inline off
normalize_loop:
    for (int i = 0; i < N; i++) {
        #pragma HLS PIPELINE off
        out[i] = (in[i] > 100) ? 100 : in[i];
    }
}

// Stage 2: Greedy filter: keep only large values
void greedy_filter(int in[N], int out[N]) {
    #pragma HLS inline off
filter_loop:
    for (int i = 0; i < N; i++) {
        #pragma HLS PIPELINE off
        out[i] = (in[i] > 50) ? in[i] : 0;
    }
}

// Stage 3: Accumulate score
void accumulate(int in[N], int &result) {
    #pragma HLS inline off
    int sum = 0;
acc_loop:
    for (int i = 0; i < N; i++) {
        #pragma HLS PIPELINE off
        sum += in[i];
    }
    result = sum;
}

void greedy_dataflow_top(int input[N][N], int &output) {

    int norm_buf[N];
    int greedy_buf[N];
    for(int i=0;i<N;i++)
    {
        #pragma HLS PIPELINE off
        normalize(input[i], norm_buf);
        greedy_filter(norm_buf, greedy_buf);
        accumulate(greedy_buf, output);
    }
}
   

```
4. Because the main factor limiting throughput is memory ports, by partitioning arrays by a factor of 2 we can increase throughput by that factor while not increasing area compared to the first exercise.
```cpp
#define N 64


// Stage 1: Normalize input
void normalize(int in[N], int out[N]) {
    #pragma HLS ARRAY_PARTITION variable=in dim=1 type=cyclic factor=2
    #pragma HLS ARRAY_PARTITION variable=out dim=1 type=cyclic factor=2
    #pragma HLS inline off
normalize_loop:
    for (int i = 0; i < N; i++) {
        out[i] = (in[i] > 100) ? 100 : in[i];
    }
}

// Stage 2: Greedy filter: keep only large values
void greedy_filter(int in[N], int out[N]) {
    #pragma HLS inline off
filter_loop:
    for (int i = 0; i < N; i++) {
        out[i] = (in[i] > 50) ? in[i] : 0;
    }
}

// Stage 3: Accumulate score
void accumulate(int in[N], int &result) {
    #pragma HLS inline off
    int sum = 0;
acc_loop:
    for (int i = 0; i < N; i++) {
        sum += in[i];
    }
    result = sum;
}

void datapath1(int input[N][N], int &output) {


    int norm_buf[N];
    int greedy_buf[N];
    
    #pragma HLS ARRAY_PARTITION variable=norm_buf dim=1 type=cyclic factor=2
    #pragma HLS ARRAY_PARTITION variable=greedy_buf dim=1 type=cyclic factor=2
    main:for(int i=0;i<N;i++)
    {
        #pragma HLS PIPELINE II=1
        normalize(input[i], norm_buf);
        greedy_filter(norm_buf, greedy_buf);
        accumulate(greedy_buf, output);
    }

}
   

```

5.
| metric          | Baseline |Inline         | Fully Iterative | Latency Reduction(Parallelization) |
| --------------- | -------- |----------------|-----------------| ---------------------------------- |
| Latency(Cycles) |     2058   |      34      |         33025        |     1034             |
| LUTs            |      11898    |       4479        |      395           |      11777            |
| FFs             |    9488     |     477           |     151            |          9398        |
| DSPs            |     0     |        0        |       0          |          0        |
| BRAMs           |    0      |         0       |       1          |        0          |

As we can see inline is the pragma that makes the most difference, not only is the one with most throughput by far but it's also the second one with less resource usage. This makes it by far the best option. However, dependending on your objectives you may prefer the fully iterative or the latency reduction versions.
