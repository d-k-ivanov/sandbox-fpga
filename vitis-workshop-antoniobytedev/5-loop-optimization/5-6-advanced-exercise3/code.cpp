void merge(int a[128], int b[128], int c[128], int out[128]) {
    #pragma HLS ARRAY_PARTITION variable=out dim=1 type=cyclic factor=2
    

    loop1:for (int i = 0; i < 128; i++) {
       a[i]= a[i]>>1;
    }

    loop2:for (int j = 0; j < 128; j++) {
        out[j] += c[j];
    }
    
    loop3:for (int k = 0; k < 128; k++) {
        out[k] += b[k] + a[k];
    }
}