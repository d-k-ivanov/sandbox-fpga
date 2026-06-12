# Task
Create a project in Vitis HLS with the attached code for the xa7a12tcpg238-2I card using a clock period of 10 ns. For each of the points below, create a new solution, provide a reasoned explanation of the pragmas and code changes, perform the synthesis, attach the results table, explain the consistency of these results, and provide reasoned answers to the questions.

1. Baseline Synthesis and Architecture Analysis
Synthesize the function without making any modifications. Based on the obtained "report," what type of architecture does Vitis HLS generate? Does it apply any implicit pragmas?

2. Add the pragma Inline in all subfunctions. How does throughput change? And area?

3. Fully Iterative Architecture
Modify the code from exercise 1 using only the necessary pragmas to make the architecture fully iterative (reducing area and increasing latency). Now replace all if statements with ternary operators. Does throughput change? And area?

4. Latency Reduction (Parallelization)
Use only the necessary pragmas to try and reduce the latency of the original code (Point 1) by a factor of 2 (in practice, it will be slightly less). Describe which results indicate that this parallelization has indeed been performed.

5. Comparative Analysis
Create a comparative table with the results of the three previous architectures and reason which one would be the most efficient in relation to throughput and resource utilization.

| metric          | Baseline |Inline          | Fully Iterative | Latency Reduction(Parallelization) |
| --------------- | -------- |----------------|-----------------| ---------------------------------- |
| Latency(Cycles) |          |                |                 |                  |
| LUTs            |          |                |                 |                  |
| FFs             |          |                |                 |                  |
| DSPs            |          |                |                 |                  |
| BRAMs           |          |                |                 |                  |