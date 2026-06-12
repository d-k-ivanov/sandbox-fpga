#include <ap_int.h>
#define N 256

void datapath1(ap_int<32> A[N], ap_int<32> B[N], ap_int<32> C[N]) {
ap_int<32> buffer[N];
for(int i=0;i<N;i++)
{
#pragma HLS PIPELINE off
buffer[i]=A[i];
}
    for (int i = 0; i < N; i += 4) {
        for (int j = 0; j < 4; j++) {
            #pragma HLS UNROLL factor=4
            int idx = i + j;
            C[idx] = buffer[idx] + B[idx];
        }
    }
}