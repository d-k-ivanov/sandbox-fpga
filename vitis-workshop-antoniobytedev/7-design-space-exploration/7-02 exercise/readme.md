# Task
Create a project in Vitis HLS with the attached code for the xa7a12tcpg238-2I card using a clock period of 10 ns. For each of the points below, create a new solution, provide a reasoned explanation of the pragmas and code changes, perform the synthesis, attach the results table, explain the consistency of these results, and provide reasoned answers to the questions.

1. Baseline Synthesis and Architecture Analysis
Synthesize the function without making any modifications. Based on the obtained "report," what type of architecture does Vitis HLS generate? Does it apply any implicit pragmas?

2. Fully Iterative Architecture
Use only the necessary pragmas to make the architecture fully iterative (reducing area and increasing latency). Now replace all if statements with ternary operators. Does throughput change? And area?

3. Latency Reduction (Parallelization)
Use only the necessary pragmas to try and reduce the latency of the original code (Point 1) by a factor of 8 (in practice, it will be slightly less). Describe which results indicate that this parallelization has indeed been performed.

4. Comparative Analysis
Create a comparative table with the results of the three previous architectures and reason which one would be the most efficient in relation to throughput and resource utilization.

# Finished table
| metric          | Baseline | Fully Iterative | Latency Reduction(Parallelization) |
| --------------- | -------- | --------------- | ---------------------------------- |
| Latency(Cycles) |          |                 |                                    |
| LUTs            |          |                 |                                    |
| FFs             |          |                 |                                    |
| DSPs            |          |                 |                                    |
| BRAMs           |          |                 |                                    |