#define N 128

void bubble_sort(int A[N]) {
    #pragma HLS ARRAY_PARTITION variable=A type=complete
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - 1; j++) {
            #pragma HLS PIPELINE II=1
            int tmp=A[j];
            if (A[j] > A[j + 1]) {
                A[j] = A[j + 1];
                A[j + 1] = tmp;
            }
        }
    }
}
