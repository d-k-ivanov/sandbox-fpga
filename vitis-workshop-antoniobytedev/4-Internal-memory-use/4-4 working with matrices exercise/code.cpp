void matvec_mult(int A[64][64], int x[64], int y[64]) {
    for (int i = 0; i < 64; i++) {
        int sum = 0;
        #pragma HLS PIPELINE II=1
        for (int j = 0; j < 64; j++) {

            sum += A[i][j] * x[j];
        }
        y[i] = sum;
    }
}