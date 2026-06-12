#define N 128
void loop_merge(int A[N][N], int B[N]) {
int sum[N];
sum_loop:
for (int i = 0; i < N; i++) {
    sum[i]=0;
    for(int j=0;j<N;j++)
    {
        sum[i]=A[i][j];
    }
}

scale_loop:
for (int i = 0; i < N; i++) {
    B[i] = sum[i] * 2;
}

}