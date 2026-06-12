# Solution
- **inline off solution**
```cpp
#define N 64

// Subfunction #1: Scales values
void scale_array(int A[N], int B[N]) {
    #pragma HLS inline off
scale_loop:
    for(int i = 0; i < N; i++) {
        #pragma HLS PIPELINE II=1
        B[i] = A[i] * 2;
    }
}


// Subfunction #2: Computes partial scores
void compute_score(int A[N], int B[N], int scores[N]) {
    #pragma HLS inline off
score_loop:
    for(int i = 0; i < N; i++) {
        #pragma HLS PIPELINE II=1
        scores[i] = A[i] * B[i];
    }
}

void datapath1(int A[N][N],int B[N][N],int out[N][N]) {

    for(int i=0;i<N;i++)
    {
        #pragma HLS UNROLL factor=8
        scale_array(A[i], B[i]);
        compute_score(A[i],B[i],out[i]);
    }

}

```
- **inline solution**
```cpp
#define N 64

// Subfunction #1: Scales values
void scale_array(int A[N], int B[N]) {
    #pragma HLS inline 
scale_loop:
    for(int i = 0; i < N; i++) {
        #pragma HLS PIPELINE II=1
        B[i] = A[i] * 2;
    }
}


// Subfunction #2: Computes partial scores
void compute_score(int A[N], int B[N], int scores[N]) {
    #pragma HLS inline 
score_loop:
    for(int i = 0; i < N; i++) {
        #pragma HLS PIPELINE II=1
        scores[i] = A[i] * B[i];
    }
}

void datapath1(int A[N][N],int B[N][N],int out[N][N]) {

    for(int i=0;i<N;i++)
    {
        #pragma HLS UNROLL factor=8
        scale_array(A[i], B[i]);
        compute_score(A[i],B[i],out[i]);
    }

}

```

By unrolling the main loop if subfunctions are inlined we replicate them, increasing area significantly. By not inlining we only replicate the subfunction call, calling it 8 more times but not the hardware itself. In this example we don't gain anything from inlining, making the inline off architecture the clearly better choice. However, in some other use case we may gain enough throughput from inlining to justify the decision.
# Finished table
| Metric                        | **Without inline** | **With inline** 
| ----------------------------- | ---------------------- | ------------------------------- | 
| **Total Latency (cycles)**    |     8833               |               8833                  |                                    |
| **LUTs Used**                 |     722                  |           2370                      |                                    |
| **FFs Used**                  |    297                   |    1749                             |                                    |
| **BRAMs Used**                  |  0                    |     0                           |                                    |
| **DSPs Used**                  |     3                  |          24                 |                                    |