void multiple_memory_access(int a[256], int result[128]) {

    for (int i = 0; i < 128; i++) {
        #pragma HLS PIPELINE off
        result[i] = a[2 * i] + a[2 * i + 1] + a[i];

    }
}
