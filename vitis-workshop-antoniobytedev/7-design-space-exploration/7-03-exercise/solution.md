# Solution
1. This program generates an architecture that automatically applies pipeline and unrolls the evalLoop by a factor of 5.

2.
```cpp
#define order 5

void datapath1(float x[1024], float F[1024])
{

const float coef[order]={-3.4, 2, -1.25, 0.68, 1};
float sal;

 DataLoop: for (int i=0; i<1024; i++) {
    sal=0;
    #pragma HLS PIPELINE off
    evalLoop: for (int j=order-1; j>=0; j--){
    	sal=sal*x[i]+coef[j];
    }

    F[i]=sal;
 }
}
```
By applying the pragma pipeline off we can reduce area. However, in this example this increases latency exponentially.

3.

```cpp
#define order 5

void datapath1(float x[1024], float F[1024])
{

#pragma HLS ARRAY_PARTITION variable=x dim=1 type=cyclic factor=2
#pragma HLS ARRAY_PARTITION variable=F dim=1 type=cyclic factor=2
const float coef[order]={-3.4, 2, -1.25, 0.68, 1};
float sal;

 DataLoop: for (int i=0; i<1024; i++) {
    sal=0;
    #pragma HLS PIPELINE II=1
    #pragma HLS UNROLL factor=4
    evalLoop: for (int j=order-1; j>=0; j--){
    	sal=sal*x[i]+coef[j];
    }

    F[i]=sal;
 }
}
```
It is necessary to unroll this time because this way we can take advantage of all the ports of the memory by replicating hardware by a factor of 4. We only need to unroll by 4 the contents of DataLoop, as pipeline automatically fully unrolls evalLoop.


4.

# Finished table
| metric          | Baseline | Fully Iterative | Latency Reduction(Parallelization) |
| --------------- | -------- | --------------- | ---------------------------------- |
| Latency(Cycles) |     1072 |       46084          |       304                             |
| LUTs            |   1823       |      673           |       6990                             |
| FFs             |   2336       |       621          |           9004                         |
| DSPs            |       25   |         5        |                   100                 |
| BRAMs           |        0  |          0       |                       0             |

The most efficient one is the baseline, because it has the most balance between area and throughput. However, dependending on your objectives you may prefer the fully iterative or the latency reduction versions.

5. The arquitecture that is the easiest to adapt is the fully iterative, as vitis can't unroll loops with a variable number of iterations.







