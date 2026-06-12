#include <stdint.h>

#define N 32          // Length of input signal
#define K 5           // Length of kernel/filter
#define OUT_LEN (N+K-1)

void convolution_1d(int input[N], int kernel[K], int output[OUT_LEN]) {

    // Initialize output
    init_loop:
    for (int i = 0; i < OUT_LEN; i++) {
        output[i] = 0;
    }

    // Convolution accumulation
    conv_outer:
    for (int i = 0; i < N; i++) {
        conv_inner:
        for (int j = 0; j < K; j++) {
            output[i + j] += input[i] * kernel[j];
        }
    }
}
