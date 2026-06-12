# Solution
```cpp
int scale(int x[128]) {
#pragma HLS inline 
int out=0;
    scale_loop:for(int i=0;i<128;i++)
    {
        out+=x[i]*2;
    }
    return out;
}

int bias(int x) {
    return x+10;
}

int threshold(int x) {
    return (x > 100) ? 100 : x;
}

void top_function(int A[128][128], int B[128][128]) {
   outside_main: for (int i = 0; i < 128; i++) {
        inside_main:for (int j = 0; j < 128; j++) {
#pragma HLS PIPELINE II=1
            int val = scale(A[i]);
            val = bias(val);
            B[i][j] = threshold(val);
        }
    }
}
```
By inlining the functions not only do we achieve higher throughput(100 cycles more) but we also reduce the area. However, if there were multiple calls to the inlined functions it would be better to turn inline off, as it would increase area without providing much benefit.

## Finished table
| Metric                        | **Without inline** | **With inline** 
| ----------------------------- | ---------------------- | ------------------------------- | 
| **Total Latency (cycles)**    |     26241               |      26113                           |                                    |
| **LUTs Used**                 |         5379               |    5376                              |                                    |
| **FFs Used**                  |   4081              |  4076                                                          |
          
