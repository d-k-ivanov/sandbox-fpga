void scale_matrix(int a[64][64], int c[64][64], int rows) {
    for (int i = 0; i < rows; i++) {   // variable bound
        for (int j = 0; j < 64; j++) {
            #pragma HLS PIPELINE II=1
            c[i][j] = a[i][j] * 2;
        }
    }
}

void add_matrices(int a[64][64], int b[64][64], int c[64][64]) {
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 64; j++) {
            #pragma HLS PIPELINE II=1
            c[i][j] = a[i][j] + b[i][j];
        }
    }
}

void process_matrix(int a[64][64], int c[64][64]) {
    for (int i = 0; i < 64; i++) {
        preprocess_row(i);   // operation outside inner loop
        for (int j = 0; j < 64; j++) {
            #pragma HLS PIPELINE II=1
            c[i][j] = a[i][j] * 2;
        }
    }
}