#include <stdint.h>

#define N 64

// Stage 1: Normalize input
void normalize(int in[N], int out[N]) {
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
   
