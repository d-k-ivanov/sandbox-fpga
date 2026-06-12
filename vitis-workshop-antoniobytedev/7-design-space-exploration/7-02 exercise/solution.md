# Solution


1. This generates an architecture that flattens both loops into one, thus preventing automatic unroll.

2.
```cpp
#define N 64
void matrix_transpose_basic(int A[N][N], int B[N][N]) {

    outer:for(int i = 0; i < N; i++) {
        #pragma HLS LOOP_FLATTEN off
        #pragma HLS PIPELINE off
        inner:for(int j = 0; j < N; j++) {
            B[j][i] = A[i][j];
        }
    }
}
```

 By disabling loop flatten and adding the pipeline off directive in the outer loop we can make this design fully iterative,which reduces area but increments the number of cycles.

3.
```cpp
#define N 64       // Length of input signal


void matrix_transpose_basic(int A[N][N], int B[N][N]) {
    #pragma HLS ARRAY_PARTITION variable=A dim=2 type=cyclic factor=4
    #pragma HLS ARRAY_PARTITION variable=B dim=1 type=cyclic factor=4
    outer:for(int i = 0; i < N; i++) {

        #pragma HLS PIPELINE II=1
        inner:for(int j = 0; j < N; j++) {
            B[j][i] = A[i][j];
        }
    }
}
```
Because the inner loop is unrolled completely, to reduce latency by a factor of 8 we only need to partition all variables by a cyclic factor of 4, adding 4 new ports and thus increasing throughput by a factor of 4. It is important to partition the correct dimension as otherwise it will be useless.
4.


| metric          | Baseline | Fully Iterative | Latency Reduction(Parallelization) |
| --------------- | -------- | --------------- | ---------------------------------- |
| Latency(Cycles) | 4099     |      4353           |           515                         |
| LUTs            |    200   |          141       |               819                     |
| FFs             |    49    |           39      |                312                    |
| DSPs            |    0     |           0      |                  0                  |
| BRAMs           |     0    |            0     |                  0                  |

The most efficient one is the latency reduction option, because by increasing the area by a factor of 4 we can achieve 8 times more throughput.  However, dependending on your objectives you may prefer the fully iterative or the latency reduction versions.