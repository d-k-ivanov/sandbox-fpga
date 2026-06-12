#define N 256

void process_array(int in[N], int out[N]) {
    for (int i = 0; i < N; i++) {
        out[i] = in[i] * 2 + 5;
    }
}