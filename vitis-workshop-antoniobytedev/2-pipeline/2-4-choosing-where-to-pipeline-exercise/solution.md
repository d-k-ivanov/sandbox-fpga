# SOLUTION

## Pipeline insde the loop
```cpp
#define N 256
#define M 16
void compute_shift_sum(int input[N], int output[N]) {
 
    for (int i = 0; i < N; i++) {
        int sum = 0;
       #pragma HLS PIPELINE off
        inner_loop: for (int j = 0; j < M; j++) {
            sum += input[i] >> j;
            #pragma HLS PIPELINE II=1
        }
        output[i] = sum;
    }
}
```

## Pipeline outside the loop
```cpp
#define N 256
#define M 16
void compute_shift_sum(int input[N], int output[N]) {
 
    for (int i = 0; i < N; i++) {
        int sum = 0;
       #pragma HLS PIPELINE II=1
        inner_loop: for (int j = 0; j < M; j++) {
            sum += input[i] >> j;
        }
        output[i] = sum;
    }
}
```
By using pipeline outside the loop it unrolls it completely increasing performance almost twenty fold, despite it only increasing resources by a factor of 5. 

## Finished table
| Metric                        | **Without Pipelining** | **With #pragma HLS PIPELINE in the `inside loop`** | **With #pragma HLS PIPELINE in the `outside loop`** |
| ----------------------------- | ---------------------- | ------------------------------- | ---------------------------------- |
| **Total Latency (cycles)**    |       4866                 |               4099                  |               256                     |
| **LUTs Used**                 |  247                      |      393                     |       540                                   |
| **FFs Used**                  |     100                   |     133                            |    456                                |
| **DSPs Used**                 |    0                    |         0                        |      0                              |
| **BRAMs Used**                |     0                   |         0                        |       0                             |

