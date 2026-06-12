# Solution
```cpp
void brighten_image(int in[64][64], int out[64][64], int bias) {
int row_sum=0;

   outer: for (int i = 0; i < 64; i++) {
        #pragma HLS PIPELINE off
        #pragma HLS LOOP_FLATTEN
       inner: for (int j = 0; j < 64; j++) {
        
            row_sum += out[i][j]; 
            out[i][j] = in[i][j] + bias + row_sum;
        }
    }
}

```
If the loop has been flattened correctly, the name of the resulting loop should be outer_inner. This solution achieves better performance by removing the overhead between inner and outer loops.

## Finished table
| Metric                        | **Without Flattening** | **With Flattening** 
| ----------------------------- | ---------------------- | ------------------------------- | 
| **Total Latency (cycles)**    |           4481           |              4100                   |                                    |
| **LUTs Used**                 |        345               |           359                      |                                    |
| **FFs Used**                  |   214                |            320                     |                                    |
|**BRAMs Used**|0|0
|**DSPs Used**|0|0

