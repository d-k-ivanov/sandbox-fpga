#define N 64
#define UF 0

void datapath1(int img_in[N][N], int img_out[N][N]) {
    for (int i = 0; i < N; i++) {
        #pragma HLS PIPELINE off
        for (int j = 0; j < N; j++) {
            #pragma HLS PIPELINE II=1
            #pragma HLS UNROLL factor = UF2
            int pixel = img_in[i][j] + 30;
             pixel = (pixel>255) ? 255 : pixel;
            img_out[i][j] = pixel;
        }
    }
}