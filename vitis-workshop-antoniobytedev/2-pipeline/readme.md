# Pipeline
Pipelining is one of the most powerful features in HLS for increasing performance. This section dives into #pragma HLS PIPELINE and the concept of initiation interval (II), showing how to turn sequential loops into deeply pipelined hardware stages. We’ll also discuss how dependencies and loop structure affect pipeline efficiency.

## Index
- **2.1** Explaining what is pipelining.
    - Exercise about basic pipeling
- **2.2** Explaining the importance of choosing the correct II(initiation interval).
    - Exercise about choosing the correct II to not get a violation.
- **2.3** Removing false dependencies in pipelining.
    - Exercise about using the pragma HLS DEPENDENCE to remove false dependencies.
- **2.4** Explaining the differences between pipelining inside or outside a loop.
    - Exercise about how pipelining in the outer or inner loop affects throughput and area.
- **Advanced**
    - **Exercise 1** About choosing to pipeline inside or outside the loop.
    - **Exercise 2** About how removing if statements can increase throughput when pipelining.
    - **Exercise 3** About choosing where to pipeline in imperfect loops.
