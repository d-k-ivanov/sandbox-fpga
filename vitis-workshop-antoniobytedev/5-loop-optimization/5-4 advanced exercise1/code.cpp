#define N 128
void flatten_merge(int a[N][N], int b[N][N], int c[N][N]) {
int buffer[N][N];
initialize:for(int i=0;i<N;i++)
{
    #pragma HLS PIPELINE off
    for(int j=0;j<N;j++)
    {
        #pragma HLS LOOP_FLATTEN
        buffer[i][j]=a[i][j];
    }
}
main:for(int i=0;i<N;i++)
{
    #pragma HLS PIPELINE off
    for(int j=0;j<N;j++)
    {
        #pragma HLS LOOP_FLATTEN
        c[i][j]=a[i][j]+b[i][j];
    }
}
c[0][0]=buffer[0][127];
}