#define SIZE 256
void combine_arrays_reshaped(short a[SIZE], short b[SIZE], short c[SIZE], short out[SIZE]) {
    const short w1 = 2;
    const short w2 = 3;
    const short w3 = 4;

    for (int i = 0; i < SIZE; i++) {

        out[i] = a[i] * w1 + b[i] * w2 - c[i] * w3;
    }
}