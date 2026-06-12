# Solution
```cpp
void sum(int b[128], int a[128],int out[128])
{
   #pragma HLS inline off
    loop3:for (int k = 0; k < 128; k++) {
        out[k] += b[k] + a[k];
    }
}
void merge(int a[128], int b[128], int c[128], int out[128]) {
    #pragma HLS ARRAY_PARTITION variable=out dim=1 type=cyclic factor=2
    
    #pragma HLS LOOP_MERGE
    loop1:for (int i = 0; i < 128; i++) {
       a[i]= a[i]>>1;
    }
    loop2:for (int j = 0; j < 128; j++) {
        out[j] += c[j];
    }
    
    sum(b,a,out);
}
```
This is impossible because loop3 has carried dependencies with loop1 and loop2. The only way to only merge loop1 and loop2 is to execute loop3 in a sub function and **turn inline off** as it's active by default and will make the creation of the subfunction useless. Here the resource usage and throughput is similar because Vitis automatically pipelines the first architecture, making independent loops run in parallel and thus reducing latency. However, it is important to keep this in mind as it can greatly affect some designs.

## Finished Table
| Metric                        | **Without Refactoring** | **With Refactoring** 
| ----------------------------- | ---------------------- | ------------------------------- | 
| **Total Latency (cycles)**    |         265             |              263                   |                                    |
| **LUTs Used**                 |   597                     |     449                            |                                    |
| **FFs Used**                  |   167                     |       190                          |                                    |
|**BRAMs Used**|0|0
|**DSPs Used**|0|0