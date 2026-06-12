#define N 256
void top_function(int A[N], int B[N], int C[N]) {
int bufferA[N];
int bufferB[N];
for(int i=0;i<N;i++)
{
    bufferA[i] = A[i];
    bufferB[i] = B[i];
}

    for (int i = 0; i < N; i++) {
        #pragma HLS PIPELINE II=1
        #pragma HLS UNROLL factor=4
        C[i] = bufferA[i] + bufferB[i];
    }
}