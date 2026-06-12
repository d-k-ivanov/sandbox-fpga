#define N 256

typedef struct {
    float real;
    float imag;
} complex_t;

void fft(complex_t x[N], complex_t X[N]) {

    complex_t a[N];

copy_loop:
    for(int i = 0; i < N; i++) {
        a[i] = x[i];     // Copy step
    }

init_loop:
    for(int i = 0; i < N; i++) {
        // Initialize values in a deterministic and independent way
        a[i].real = a[i].real * 0.5f + 1.0f;
        a[i].imag = a[i].imag * 0.25f;
    }

transform_loop:
    for(int i = 0; i < N; i++) {
        // Arbitrary transformation, no dependency on neighbors
        float temp = a[i].real + a[i].imag;
        a[i].real = temp * 0.8f;
        a[i].imag = temp * 1.2f;
    }

write_loop:
    for(int i = 0; i < N; i++) {
        X[i] = a[i];
    }
}
