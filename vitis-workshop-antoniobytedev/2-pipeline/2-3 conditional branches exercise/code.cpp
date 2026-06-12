#define SIZE 256
#define TOKENS 64

void count_tokens(int stream[SIZE], int counts[TOKENS]) {
    int acc = 0;
    int old_token = stream[0];
    int current;

    for (int i = 0; i < SIZE; i++) {
        #pragma HLS PIPELINE off
        current = stream[i];
        if (current == old_token) {
            acc++;
        } else {
            counts[old_token] = acc;
            acc = counts[current] + 1;  
        }
        old_token = current;
    }

    counts[old_token] = acc;
}