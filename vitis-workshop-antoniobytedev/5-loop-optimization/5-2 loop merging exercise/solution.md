# Solution
```cpp
#define N 128
void loop_merge(int A[N][N], int B[N]) {
int sum[N];
#pragma HLS LOOP_MERGE
sum_loop:
for (int i = 0; i < N; i++) {
    sum[i]=0;
    for(int j=0;j<N;j++)
    {
        sum[i]=A[i][j];
    }
}

scale_loop:
for (int i = 0; i < N; i++) {
    B[i] = sum[i] * 2;
}

}
```
By merging both loops not only are we able to reduce the number of loops but also reduce the area in half.
## Finished table
| Metric                        | **Without Merging** | **With Merging** 
| ----------------------------- | ---------------------- | ------------------------------- | 
| **Total Latency (cycles)**    |                 263       |            130                     |                                    |
| **LUTs Used**                 |    194                    |    71                             |                                    |
| **FFs Used**                  |   44                     |  19                               |                                    |
|**BRAMs Used**|1|0
|**DSPs Used**|0|0