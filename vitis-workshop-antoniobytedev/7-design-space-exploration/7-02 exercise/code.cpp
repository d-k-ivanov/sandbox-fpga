#define N 128
void matrix_transpose_basic(int A[N][N], int B[N][N]) {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            B[j][i] = A[i][j];
        }
    }
}