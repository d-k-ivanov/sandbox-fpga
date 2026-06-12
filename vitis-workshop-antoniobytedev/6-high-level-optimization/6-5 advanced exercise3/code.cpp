#define N 64

// Subfunction #1: Scales values
void scale_array(int A[N], int B[N]) {
scale_loop:
    for(int i = 0; i < N; i++) {
        #pragma HLS PIPELINE II=1
        B[i] = A[i] * 2;
    }
}


// Subfunction #2: Computes partial scores
void compute_score(int A[N], int B[N], int scores[N]) {
score_loop:
    for(int i = 0; i < N; i++) {
        #pragma HLS PIPELINE II=1
        scores[i] = A[i] * B[i];
    }
}

void top_function(int A[N][N],int B[N][N],int out[N][N]) {

    for(int i=0;i<N;i++)
    {
        scale_array(A[i], B[i]);
        compute_score(A[i],B[i],out[i]);
    }

}
