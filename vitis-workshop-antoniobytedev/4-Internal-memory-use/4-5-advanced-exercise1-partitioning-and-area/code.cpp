#define N 128

void partition_exercise_opt(int A[N], int B[N]) {
    for (int i = 0; i < N - 2; i++) {
        #pragma HLS PIPELINE II=1
        int sum = A[i] + A[i + 1] + A[i + 2];
        B[i] = sum;

    }
}