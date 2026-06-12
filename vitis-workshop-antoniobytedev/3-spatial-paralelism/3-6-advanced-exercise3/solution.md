# Solution
```cpp
#define N 64
#define UF 2

void datapath1(int img_in[N][N], int img_out[N][N]) {
    for (int i = 0; i < N; i++) {
        #pragma HLS PIPELINE off
        for (int j = 0; j < N; j++) {
            #pragma HLS PIPELINE II=1
            #pragma HLS UNROLL factor = UF2
            int pixel = img_in[i][j] + 30;
             pixel = (pixel>255) ? 255 : pixel;
            img_out[i][j] = pixel;
        }
    }
}
```
Combining pipeline and unroll is much more efficient. Not only do we achieve double the throughput, but we also use a similar number of resources. This is because pipelining allows us to reduce the iteration latency significantly, compared to only unrolling.
# Finished table
| metric                          | Previous Exercise | Max Unroll Factor(2) |
| ------------------------------- | ----------------- | -------------------- |
| Latency in second loop (cycles) | 4225              | 2052                 |
| LUTs Used                       | 455               | 422                  |
| FFs Used                        | 161               | 244                  |
| DSPs Used                       | 0                 | 0                    |
| BRAMs Used                      | 0                 | 0                    |

