# Problems in Unrolling – Dependencies Between Iterations
In FPGA designs using Vitis HLS, loop unrolling is a powerful technique for increasing parallelism by executing multiple iterations of a loop simultaneously. However, unrolling requires that each iteration of the loop can execute independently without depending on the results of another iteration. If there are dependencies between iterations, Vitis HLS cannot safely unroll the loop, preventing you from fully utilizing the FPGA's parallel resources and limiting your achievable throughput.

## Example
Consider the following simple accumulation loop, which calculates the sum of all elements in an array:

```cpp
void sum_array(double in[256], int &sum) {
    sum = 0;
    
    for (int i = 0; i < 256; i++) {
        #pragma HLS UNROLL
        sum += in[i];
    }
}
```
In this example, each iteration depends on the sum value calculated in the previous iteration, creating a loop-carried dependency. Because the current iteration cannot proceed without the result of the previous iteration, unrolling this loop is not possible. Attempting to unroll this structure will result in either a synthesis error or Vitis HLS ignoring the unroll directive, leaving the loop to execute sequentially. This limits your design's ability to achieve high throughput and prevents the FPGA from executing multiple additions in parallel.

## The Solution
To allow unrolling, you need to restructure your code to remove dependencies between iterations. For accumulation patterns like this, you can use a parallel reduction tree to compute the sum without sequential dependencies, enabling unrolling.

```cpp
void sum_array_unrolled(double in[256], double &sum) {
double partial_sums[16] = {0};
 
    for (int i = 0; i < 256; i++) {
        #pragma HLS UNROLL
        partial_sums[i % 16] += in[i];
    }

    sum=0;
    for (int j = 0; j < 16; j++) {
        #pragma HLS UNROLL
        sum += partial_sums[j];
    }

}
```
| metric | Without refactor | Refactored |
| ------ | ---------------- | ---------- |
| Cycles | 3579             | 180        |
| LUTs   | 4029             | 8136       |
| FFs    | 7326             | 4956       |
| BRAMs  | 0                | 4          |
| DSPs   | 3                | 15         |

As we can see our code structure affects performance greatly, as we were able to reduce the number of cycles 20 fold, which would have been impossible had we not refactored.

## Why Avoiding Dependencies Matters
If your loops have dependencies between iterations, you cannot unroll them, and your design will execute sequentially, wasting the FPGA’s parallel compute capabilities. By restructuring your code to eliminate these dependencies, you allow Vitis HLS to unroll your loops fully or partially, significantly improving throughput by allowing your design to process multiple data elements in parallel. This enables your FPGA to execute your workloads faster while maintaining efficient use of the hardware resources you have available.
