#define N 256
#define M 16
void compute_shift_sum(int input[N], int output[N]) {
 
    for (int i = 0; i < N; i++) {
        int sum = 0;
       #pragma HLS PIPELINE off
        inner_loop: for (int j = 0; j < M; j++) {
            sum += input[i] >> j;
            #pragma HLS PIPELINE off
        }
        output[i] = sum;
    }
}