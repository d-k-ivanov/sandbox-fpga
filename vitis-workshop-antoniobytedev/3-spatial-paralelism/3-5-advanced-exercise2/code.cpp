#define N 64

#define UF1 0
#define UF2 0
void brighten_image(int img_in[N][N], int img_out[N][N]) {
    outer:for (int i = 0; i < N; i++) {
        #pragma HLS PIPELINE off
        #pragma HLS UNROLL factor = UF1
        inner:for (int j = 0; j < N; j++) {
            #pragma HLS PIPELINE off
            #pragma HLS UNROLL factor = UF2
            int pixel = img_in[i][j] + 30;
             pixel = (pixel>255) ? 255 : pixel;
            img_out[i][j] = pixel;
        }
    }
}