# Task
Create a project in Vitis HLS with the attached code for the xa7a12tcpg238-2I card using a clock period of 10 ns. For each of the points below, create a new solution, provide a reasoned explanation of the pragmas and code changes, perform the synthesis, attach the results table, explain the consistency of these results, and provide reasoned answers to the questions.

1. Baseline Synthesis and Architecture Analysis
Synthesize the function without making any modifications. Based on the obtained "report," what type of architecture does Vitis HLS generate? Does it apply any implicit pragmas? 

2. Add the pragma loop merge at the beginning of the fft function. How does throughput change? And area?

3. Fully Iterative Architecture
Modify the code from exercise 2 using only the necessary pragmas to make the architecture fully iterative (reducing area and increasing latency).

4. Latency Reduction (Parallelization)
Unroll all loops by a factor of 4. Why doesn't throughput increase?

5. Comparative Analysis
Create a comparative table with the results of the three previous architectures and reason which one would be the most efficient in relation to throughput and resource utilization.


| metric          | Baseline |Merged          | Fully Iterative | Latency Reduction(Parallelization) |
| --------------- | -------- |----------------|-----------------| ---------------------------------- |
| Latency(Cycles) |          |                |                 |                  |
| LUTs            |          |                |                 |                  |
| FFs             |          |                |                 |                  |
| DSPs            |          |                |                 |                  |
| BRAMs           |          |                |                 |                  |