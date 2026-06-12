#define N 128
void datapath1(int A[N], int B[N]) {
#pragma HLS ARRAY_PARTITION variable=B dim=1 type=cyclic factor=2
#pragma HLS LOOP_MERGE
copy_loop:
for (int i = 0; i < N; i++) {
    B[i] = A[i];
}


scale_loop:
for (int i = 0; i < N; i++) {
    B[i] = B[i] * 2 +5;
}

}