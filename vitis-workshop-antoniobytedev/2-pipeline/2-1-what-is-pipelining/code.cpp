#define N 256

void my_func(int a[N], int b[N], int c[N]) {
    for (int i = 0; i < N; i++) {
        #pragma HLS PIPELINE off
        c[i] = a[i] + b[i];
    }
} 

void add_arrays(int a[N], int b[N], int c[N]) {
    for (int i = 0; i < N; i++) {
        /*because this loop has more than 64 iterations vitis will
        try to pipeline it automatically,
         so it's important to turn pipeline off to compare the results*/
        #pragma HLS PIPELINE off
        c[i] = a[i] + b[i];
    }
} 

void add_arrays_pipeline(int a[N], int b[N], int c[N]) {
    for (int i = 0; i < N; i++) {
        #pragma HLS PIPELINE II=1
        c[i] = a[i] + b[i];
    }
}
