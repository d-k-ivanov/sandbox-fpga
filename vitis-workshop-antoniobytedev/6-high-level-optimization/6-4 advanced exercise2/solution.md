# Solution
## Dataflow Solution
```cpp
#define N 64
#define K 8
void add_bias_loop(int row, int in_row[N], int out_row[N]) {
    #pragma HLS inline off
    for (int j = 0; j < N; j++) {
        out_row[j] = in_row[j] + row; 
    }
}

void scale_loop(int in_row[N], int out_row[N]) {
    #pragma HLS inline off
    for (int j = 0; j < N; j++) {
        out_row[j] = in_row[j] * 3; 
    }
}

void activation_loop(int in_row[N], int out_row[N]) {
    #pragma HLS inline off
    for (int j = 0; j < N; j++) {
        int v = in_row[j];
        if (v > 255) v = 255;
        if (v < 0)   v = 0;
        out_row[j] = v;
    }
}

void process_image(int A[K][N], int B[K][N]) {
    for (int i = 0; i < K; i++) {
        int tmp1[N], tmp2[N];
        #pragma HLS DATAFLOW
        add_bias_loop(i,      A[i],  tmp1);
        scale_loop(           tmp1,  tmp2);
        activation_loop(      tmp2,  B[i]);
    }
}
```
## Inline solution
```cpp
#define N 64
#define K 8
void add_bias_loop(int row, int in_row[N], int out_row[N]) {
    #pragma HLS inline
    for (int j = 0; j < N; j++) {
        out_row[j] = in_row[j] + row; 
    }
}

void scale_loop(int in_row[N], int out_row[N]) {
    #pragma HLS inline
    for (int j = 0; j < N; j++) {
        out_row[j] = in_row[j] * 3; 
    }
}

void activation_loop(int in_row[N], int out_row[N]) {
    #pragma HLS inline
    for (int j = 0; j < N; j++) {
        int v = in_row[j];
        if (v > 255) v = 255;
        if (v < 0)   v = 0;
        out_row[j] = v;
    }
}

void process_image(int A[K][N], int B[K][N]) {
    for (int i = 0; i < K; i++) {
        int tmp1[N], tmp2[N];
        add_bias_loop(i,      A[i],  tmp1);
        scale_loop(           tmp1,  tmp2);
        activation_loop(      tmp2,  B[i]);
    }
}
```
The inline version has more throughput but the dataflow version has considerably less area, as the code inside the functions isn't replicated. The dataflow architecture is considerably more balanced and in most use cases is the better one. However, if we are only interested in throughput inline is the way to go.
| Metric                        | **With INLINE** | **With DATAFLOW** 
| ----------------------------- | ---------------------- | ------------------------------- | 
| **Total Latency (cycles)**    |       260             |      654                           |                                    |
| **LUTs Used**                 |   8473                    |  525                               |                                    |
| **FFs Used**                  |  3783                     |  271                               |                                    |
| **BRAMs Used**                  |  0                    |   2                             |                                    |
| **DSPs Used**                  |  0                     |   0                        |                                    |