# Solution
```cpp
#define N 128

void merge(int a[N][N], int b[N][N], int c[N][N]) {
int buffer[N][N];
#pragma HLS LOOP_MERGE
initialize:for(int i=0;i<N;i++)
{
    #pragma HLS PIPELINE off
    inner1:for(int j=0;j<N;j++)
    {
        #pragma HLS LOOP_FLATTEN
        buffer[i][j]=a[i][j];
    }
}
main:for(int i=0;i<N;i++)
{
    #pragma HLS PIPELINE off
    inner2:for(int j=0;j<N;j++)
    {
        #pragma HLS LOOP_FLATTEN
            c[i][j]=a[i][j]+b[i][j];
    }
}
c[0][0]=buffer[0][127];
}
void prevent_merge(int a[N][N], int b[N][N], int c[N][N]) {
int buffer[N][N];
#pragma HLS LOOP_MERGE
initialize:for(int i=0;i<N;i++)
{
    #pragma HLS PIPELINE off
    inner1:for(int j=0;j<N;j++)
    {
        #pragma HLS LOOP_FLATTEN off
        buffer[i][j]=a[i][j];
    }
}
main:for(int i=0;i<N;i++)
{
    #pragma HLS PIPELINE off
    inner2:for(int j=0;j<N;j++)
    {
        #pragma HLS LOOP_FLATTEN off
        c[i][j]=a[i][j]+b[i][j];
    }
}
c[0][0]=buffer[0][127];
}
```
By turning loop flattening only outer loops can be merged. The result is a loop with N iterations containing bof inner1 and inner2. By allowing loop flattening the result is one loop with N*N iterations that combine inner1 and inner2 which leads to double the throughput while using around the same number of resources, making the architecture using flattening the superior option.
## Finished Table
| Metric                        | **Without Flattening** | **With Flattening** 
| ----------------------------- | ---------------------- | ------------------------------- | 
| **Total Latency (cycles)**    |        33922            |               16389                  |                                    |
| **LUTs Used**                 |    379                  | 377                                |                                    |
| **FFs Used**                  |   121                     | 157                               |                                    |
|**BRAMs Used**|32|32
|**DSPs Used**|0|0