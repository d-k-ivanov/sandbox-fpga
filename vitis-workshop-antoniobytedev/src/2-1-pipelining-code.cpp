void add_arrays(int a[256], int b[256], int c[256]) {
    for (int i = 0; i < 256; i++) {
        /*because this loop has more than 64 iterations vitis will
        try to pipeline it automatically,
         so it's important to turn pipeline off to compare the results*/
        #pragma HLS PIPELINE off
        c[i] = a[i] + b[i];
    }
} 

void add_arrays_pipeline(int a[256], int b[256], int c[256]) {
    for (int i = 0; i < 256; i++) {
        #pragma HLS PIPELINE II=1
        c[i] = a[i] + b[i];
    }
}

#define N 1024
void offset(float in[N], float out[N]) {
    for (int i = 0; i < N; i++) {
        #pragma HLS PIPELINE off
        out[i] = in[i] + 10.0f;
    }
}

#define N 1024
void offset_pipeline(float in[N], float out[N]) {
    for (int i = 0; i < N; i++) {
        #pragma HLS PIPELINE off
        out[i] = in[i] + 10.0f;
    }
}

