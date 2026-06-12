# Solution
1. This generates an architecture that automatically pipelines the inside loop. By replacing if statements by ternary operators we greatly reduce the number of cycles and, by a much smaller amount, reduce area. This makes the ternary version far superior to the baseline one.

```cpp
 #define SIZE 256
 void insertion_sort(int A[SIZE], int B[SIZE]) 
 {

 L1:for(int i = 0; i < SIZE; i++) 
    {
        int item = A[i];
        L2:for(int j = SIZE-1; j >= 0; j-- ) 
        {
            int t;
            bool check;
            check=j<=i&j > 0 && B[j-1] > item;
            t =(j>i)? B[j]:t;
            t=(check) ?B[j-1]:t;
            t=(!check)?item:t;
            item=(check&&j>0)?B[j-1]:item;
           

            B[j] = t;  
        }
    }
}

```
2.
By disabling pipeline we can make this design fully iterative,which reduces area but increments the number of cycles.However, the decrease in area is insignificant while the number of cycles is thrice as much.
```cpp
#define SIZE 256

void insertion_sort(int A[SIZE], int B[SIZE]) 
 {

 L1:for(int i = 0; i < SIZE; i++) 
    {
        
        int item = A[i];
        L2:for(int j = SIZE-1; j >= 0; j-- ) 
        {
            #pragma HLS PIPELINE off
            int t;
            bool check;
            check=j<=i&j > 0 && B[j-1] > item;
            t =(j>i)? B[j]:t;
            t=(check) ?B[j-1]:t;
            t=(!check)?item:t;
            item=(check&&j>0)?B[j-1]:item;
           

            B[j] = t;  
        }
    }
}

```
3. By unrolling the innermost loop by a factor of 16 and partitioning memory A by a factor of 8 and memory B by a factor of 16 we can reduce latency by a factor of 16.
```cpp
#define SIZE 256

void insertion_sort(int A[SIZE], int B[SIZE]) 
 {

#pragma HLS ARRAY_PARTITION variable=A dim=1 type=cyclic factor=8
#pragma HLS ARRAY_PARTITION variable=B dim=1 type=cyclic factor=16
 L1:for(int i = 0; i < SIZE; i++) 
    {
        
        int item = A[i];
        L2:for(int j = SIZE-1; j >= 0; j-- ) 
        {
            #pragma HLS PIPELINE II=1
            #pragma HLS UNROLL factor=16
            int t;
            bool check;
            check=j<=i&j > 0 && B[j-1] > item;
            t =(j>i)? B[j]:t;
            t=(check) ?B[j-1]:t;
            t=(!check)?item:t;
            item=(check&&j>0)?B[j-1]:item;
           

            B[j] = t;  
        }
    }
}

```

4. 

| metric          | Baseline |Baseline ternary| Fully Iterative | Latency Reduction(Parallelization) |
| --------------- | -------- |----------------|-----------------| ---------------------------------- |
| Latency(Cycles) |    132609      |  67073              |  197377               |     4100             |
| LUTs            |    345      |      235          |      227           |    267              |
| FFs             |     153     |       152         |         107        |   2234               |
| DSPs            |   0       |        0        |               0  |       0           |
| BRAMs           |    0      |         0       |               0  |        0          |

The most efficient option here is the baseline ternary as it has the best balance between resource usage and throughput.  However, dependending on your objectives you may prefer the fully iterative or the latency reduction versions.
