 1. This generates an architecture that automatically pipelines all loops.

 2. By loop merging we reduce latency by 100 cycles and reducing LUTs by half. The only downside is a slight increase in FFs.
```cpp
#define N 128

void greedy_score(float weights[N], float values[N], float score_out[N], float &max_score, float threshold) {
    max_score = 0.0;

    #pragma HLS LOOP_MERGE
    calc_loop:
    for(int i = 0; i < N; i++) {
            score_out[i] =(values[i] > threshold) ? values[i] / weights[i]:0;
    }

    max_loop:
    for(int j = 0; j < N; j++) {
        
            max_score = (score_out[j] > max_score)? score_out[j]:max_score;
    }
}

```
 3. The main benefit of doing a fully iterative design is reducing FFs usage by half. However, this increases latency significantly.
```cpp
#define N 128

void greedy_score(float weights[N], float values[N], float score_out[N], float &max_score, float threshold) {
    max_score = 0.0;

    calc_loop:
    for(int i = 0; i < N; i++) {
        #pragma HLS PIPELINE off
            score_out[i] =(values[i] > threshold) ? values[i] / weights[i]:0;
    }

    max_loop:
    for(int j = 0; j < N; j++) {
        #pragma HLS PIPELINE off
            max_score = (score_out[j] > max_score)? score_out[j]:max_score;
    }
}
```
 4. We spend more than double the resources but we can't achieve double throughput due to an II violation caused by a carried data dependency.
```cpp
#define N 128

void datapath1(float weights[N], float values[N], float score_out[N], float &max_score, float threshold) {
    max_score = 0.0;

    #pragma HLS ARRAY_PARTITION variable=values dim=1 type=cyclic factor=2
    #pragma HLS ARRAY_PARTITION variable=weights dim=1 type=cyclic factor=2
    #pragma HLS ARRAY_PARTITION variable=score_out dim=1 type=cyclic factor=2
    //#pragma HLS LOOP_MERGE
    calc_loop:
    for(int i = 0; i < N; i++) {
        #pragma HLS PIPELINE II=1
        #pragma HLS UNROLL factor=2
            score_out[i] =(values[i] > threshold) ? values[i] / weights[i]:0;
            max_score = (score_out[i] > max_score)? score_out[i]:max_score;
    }     
}

```
 5.
 
 
 metric          | Baseline |Merged          | Fully Iterative | Latency Reduction(Parallelization) |
| --------------- | -------- |----------------|-----------------| ---------------------------------- |
| Latency(Cycles) |    407      |     273     |      2562           |       145           |
| LUTs            |       1126   |      522   |       481          |           774       |
| FFs             |       664   |       786   |        348         |           1238       |
| DSPs            |      0    |        0        |        0         |            0      |
| BRAMs           |      0    |        0        |        0         |            0      |

All designs are similar in performance to area and the best one depends only on your main objective, prioritizing area, throughput or finding a balance of both.