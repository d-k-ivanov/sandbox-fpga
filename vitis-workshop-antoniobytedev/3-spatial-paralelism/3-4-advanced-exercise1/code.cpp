#define N 16

void matrix(int in[N][N],int out[N][N])
{
    for(int i=0;i<N;i++)
    {
        #pragma HLS PIPELINE off
        for(int j=0;j<N;j++)
        { 
            #pragma HLS PIPELINE off
            out[j][i]=in[i][j]*2;
        }
    }
}