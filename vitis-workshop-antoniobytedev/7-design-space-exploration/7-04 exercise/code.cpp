#define N 64
#define M 128
void prefixSum2D(int arr[N][M], int prefix[N][M]) {
    

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            
            // Start with original value
            prefix[i][j] = arr[i][j];
            
            // Add value from top cell if it exists
            if (i > 0) {
                prefix[i][j] += prefix[i - 1][j];
            }
            
            // Add value from left cell if it exists
            if (j > 0) {
                prefix[i][j] += prefix[i][j - 1];
            }
            
            // Subtract overlap from top-left diagonal if it exists
            if (i > 0 && j > 0) {
                prefix[i][j] -= prefix[i - 1][j - 1];
            }
        }
    }
}