void read_data(int in[256], int buf[256]) {
    for (int i = 0; i < 256; i++) {
        #pragma HLS UNROLL factor=2
        buf[i] = in[i];
    }
}

void transform_data(int buf[256], int temp[256]) {
    for (int i = 0; i < 256; i++) {
        #pragma HLS UNROLL factor=2
        temp[i] = buf[i] * buf[i]; // square
    }
}

void write_data(int temp[256], int out[256]) {
    for (int i = 0; i < 256; i++) {
        #pragma HLS UNROLL factor=2
        out[i] = temp[i];
    }
}

void top_sequential(int in[256], int out[256]) {
    int buf[256], temp[256];
    read_data(in, buf);
    transform_data(buf, temp);
    write_data(temp, out);
}
