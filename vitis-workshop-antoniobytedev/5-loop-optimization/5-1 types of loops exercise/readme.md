# Task
Consider the following three implementations of a simple matrix operation in Vitis HLS. Each corresponds to one of the three loop types: perfect, semi-perfect, and imperfect.

Identify the type of each loop (perfect, semi-perfect, or imperfect).

Synthesize them with Vitis HLS and observe the differences in throughput and resource usage.

Restructure the imperfect loop so that it becomes perfect, and explain why this improves pipelining and unrolling opportunities.