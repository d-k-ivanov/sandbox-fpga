#define N 16

void pascal_triangle(int P[N][N]) {
    #pragma HLS ARRAY_PARTITION variable=P dim=2 type=cyclic factor=2
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= i; j++) {
            P[i][j] =(j==0||j==1) ? 1 : P[i - 1][j - 1] + P[i - 1][j];
        }
    }
}