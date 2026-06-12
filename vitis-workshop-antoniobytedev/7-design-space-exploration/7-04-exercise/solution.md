# Solution
1. This generates an architecture that flattens both loops into one, thus preventing automatic unroll. By replacing if statements by ternary operators we greatly reduce the number of cycles at the expense of increasing the use of resources a little. This is a great tradeoff as we get an increase in throughput several times bigger than in area.
```cpp
#define N 64
#define M 128
void prefixSum2D(int arr[N][M], int prefix[N][M]) {
    

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            
            // Start with original value
            prefix[i][j] = arr[i][j];
            
            // Add value from top cell if it exists

                prefix[i][j] = (i>0)? prefix[i][j]+ prefix[i - 1][j]:prefix[i][j];
            
            
            // Add value from left cell if it exists
            
                prefix[i][j] = (j>0)?prefix[i][j]+ prefix[i][j - 1]:prefix[i][j];
            
            
            // Subtract overlap from top-left diagonal if it exists
            prefix[i][j]=(i > 0 && j > 0) ? prefix[i][j]-prefix[i-1][j-1]:prefix[i][j];
           
            }
        }
    }

```
2. By disabling loop flatten and adding the pipeline off directive in the inner loop we can make this design fully iterative,which reduces area but increments the number of cycles by a factor of 2.

```cpp
#define N 64
#define M 128
void prefixSum2D(int arr[N][M], int prefix[N][M]) {
    

    for (int i = 0; i < N; i++) {
        #pragma HLS PIPELINE off
        for (int j = 0; j < M; j++) {
            
            // Start with original value
            prefix[i][j] = arr[i][j];
            
            // Add value from top cell if it exists

                prefix[i][j] = (i>0)? prefix[i][j]+ prefix[i - 1][j]:prefix[i][j];
            
            
            // Add value from left cell if it exists
            
                prefix[i][j] = (j>0)?prefix[i][j]+ prefix[i][j - 1]:prefix[i][j];
            
            
            // Subtract overlap from top-left diagonal if it exists
            prefix[i][j]=(i > 0 && j > 0) ? prefix[i][j]-prefix[i-1][j-1]:prefix[i][j];
           
            }
        }
    }

```

3. By unrolling the innermost loop and turning loop flatten off and partitioning both memories by a factor of 2 we can achieve almost 3 times the output from baseline ternary.
```cpp
#define N 64
#define M 128
void prefixSum2D(int arr[N][M], int prefix[N][M]) {
    
#pragma HLS ARRAY_PARTITION variable=arr dim=2 type=cyclic factor=2
#pragma HLS ARRAY_PARTITION variable=prefix dim=2 type=cyclic factor=2
    for (int i = 0; i < N; i++) {
        #pragma HLS LOOP_FLATTEN off
        for (int j = 0; j < M; j++) {
            #pragma HLS PIPELINE II=1
            #pragma HLS UNROLL factor=4
            // Start with original value
            prefix[i][j] = arr[i][j];
            
            // Add value from top cell if it exists

                prefix[i][j] = (i>0)? prefix[i][j]+ prefix[i - 1][j]:prefix[i][j];
            
            
            // Add value from left cell if it exists
            
                prefix[i][j] = (j>0)?prefix[i][j]+ prefix[i][j - 1]:prefix[i][j];
            
            
            // Subtract overlap from top-left diagonal if it exists
            prefix[i][j]=(i > 0 && j > 0) ? prefix[i][j]-prefix[i-1][j-1]:prefix[i][j];
           
            }
        }
    }

```

4. 


| metric          | Baseline |Baseline ternary| Fully Iterative | Latency Reduction(Parallelization) |
| --------------- | -------- |----------------|-----------------| ---------------------------------- |
| Latency(Cycles) |49157     |     16388           |        32897         |    6149             |
| LUTs            |   540       |      745          |       486          |    924             |
| FFs             |   233       |     312           |         172       |     584             |
| DSPs            |    0      |       0         |          0       |          0        |
| BRAMs           |     0     |        0        |           0      |           0       |

Here by far the most efficient design is latency reduction, as it achieves 3 times the throughput from baseline ternary without even using double the resources.  However, dependending on your objectives you may prefer the fully iterative or the latency reduction versions.
