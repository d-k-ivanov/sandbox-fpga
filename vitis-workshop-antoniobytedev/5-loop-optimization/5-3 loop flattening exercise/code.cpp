void brighten_image(int in[64][64], int out[64][64], int bias) {
int row_sum=0;

   outer: for (int i = 0; i < 64; i++) {
        #pragma HLS PIPELINE off
        #pragma HLS LOOP_FLATTEN
       if(i%2==0)
       {
           row_sum=i;
           out[i][i] = row_sum;
       }
       inner: for (int j = 0; j < 64; j++) {
            row_sum += out[i][j]; 
            out[i][j] = in[i][j] + bias + row_sum;
            
        }
    }
}