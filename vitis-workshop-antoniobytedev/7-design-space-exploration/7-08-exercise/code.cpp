#define N 128

void greedy_score(float weights[N], float values[N], float score_out[N], float &max_score, float threshold) {
    max_score = 0.0;

    calc_loop:
    for(int i = 0; i < N; i++) {
            score_out[i] =(values[i] > threshold) ? values[i] / weights[i]:0;
    }

    max_loop:
    for(int j = 0; j < N; j++) {
        
            max_score = (score_out[j] > max_score)? score_out[j]:max_score;
    }
}
