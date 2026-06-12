#define N 1024

void function(float in[N], float out[N]) {
    for (int i = 0; i < N; i++) {
        #pragma HLS PIPELINE off
        out[i] = in[i] + 10.0f;
    }
}

void offset(float in[N], float out[N]) {
    for (int i = 0; i < N; i++) {
        #pragma HLS PIPELINE off
        out[i] = in[i] + 10.0f;
    }
}

void offset_pipeline(float in[N], float out[N]) {
    for (int i = 0; i < N; i++) {
        #pragma HLS PIPELINE II=1
        out[i] = in[i] + 10.0f;
    }
}

