int scale(int x[128]) {
int out=0;
    scale_loop:for(int i=0;i<128;i++)
    {
        out+=x[i]*2;
    }
    return out;
}

int bias(int x) {
    return x+10;
}

int threshold(int x) {
    return (x > 100) ? 100 : x;
}

void top_function(int A[128][128], int B[128][128]) {
   outside_main: for (int i = 0; i < 128; i++) {
        inside_main:for (int j = 0; j < 128; j++) {
#pragma HLS PIPELINE II=1
            int val = scale(A[i]);
            val = bias(val);
            B[i][j] = threshold(val);
        }
    }
}