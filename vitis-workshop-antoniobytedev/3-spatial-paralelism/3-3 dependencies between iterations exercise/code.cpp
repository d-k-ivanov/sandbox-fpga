void cumulative_sum(double in[256], int &sum) {
    sum = 0;
    
    for (int i = 0; i < 256; i++) {
        #pragma HLS UNROLL
        sum += in[i];
        if(i%2)
        {
            sum-=2;
        }
        
    }
}