# Solution
```cpp
#define N 32

void matmulcol(int mat1[N][N], int mat2[N][N], int result[N][N]) {
    
    #pragma HLS ARRAY_PARTITION variable=mat1 dim=2 type=complete
    #pragma HLS ARRAY_PARTITION variable=mat2 dim=2 type=complete
    #pragma HLS ARRAY_PARTITION variable=result dim=2 type=complete

    row:for(int i=0;i<N;i++)
    {
        col:for(int j=0;j<N;j++)
        {
            #pragma HLS PIPELINE II=1
            result[i][j]=0;
            product:for(int k=0;k<N;k++)
            {      
                result[i][j] += mat1[i][k]*mat2[k][j];
            }
        }
    }
}

void matmulproduct(int mat1[N][N], int mat2[N][N], int result[N][N]) {
    
    #pragma HLS ARRAY_PARTITION variable=mat1 dim=2 type=complete
    #pragma HLS ARRAY_PARTITION variable=mat2 dim=2 type=complete
    #pragma HLS ARRAY_PARTITION variable=result dim=2 type=complete

    row:for(int i=0;i<N;i++)
    {
        col:for(int j=0;j<N;j++)
        {
            result[i][j]=0;
            product:for(int k=0;k<N;k++)
            {      
                #pragma HLS PIPELINE II=1
                result[i][j] += mat1[i][k]*mat2[k][j];
            }
        }
    }
}
```
The fastest version is pipelining in col, as it unrolls the innermost loop completely, replicating the area of the loop product by a factor of N. The one with the lowest area is the architecture without pipeline, pipelininc in the product loop is close second but its throughput is much better thus becoming the most balanced architecture of the 3.

## Finished table
| Metric                        | **Without Pipelining** | **Pipelining in col** | **Pipelining in product** |
| ----------------------------- | ---------------------- | ------------------------------- | ---------------------------------- |
| **Total Latency (cycles)**    |       134241                 |        1048                         | 40033                              |
| **LUTs Used**                 |     511                   |        12807                         |       528                             |
| **FFs Used**                  |     1368                   |       38282                          |1433                             |
| **DSPs Used**                 |       3                 |         96                        |      3                              |
| **BRAMs Used**                |        0                |        0                         |       0                             |

