#include <hls_math.h>
#define N 256
void normalize(int in[N], float out[N]) {
    float sum_sq = 0.0;
    firstLoop:for (int i = 0; i < N; i++) {
        #pragma HLS PIPELINE off
        sum_sq += in[i] * in[i];
    }
    float norm = 1.0 / hls::sqrt(sum_sq);

    secondLoop:for (int i = 0; i < N; i++) {
        out[i] = in[i] * norm;
    }
}