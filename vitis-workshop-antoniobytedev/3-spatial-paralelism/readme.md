# Spatial Paralelism
Once data movement is in place, it’s time to boost performance through parallel execution. This section focuses on pipelining and unrolling loops, and how these techniques can increase throughput — with careful attention to how they affect hardware resource usage.

## Index
* **3.1** Explaining the differences between unroll and pipeline and how both are used for different purposes.
    * Exercise about showing unroll effects in a loop and how to combine it with pipeline.
* **3.2** Explaining unroll further and its different types (partial and complete)
    * Exercise about choosing the best type of unroll, a partial or complete.
* **3.3** Explaining how dependency between iterations can prevent unrolling.
    * Exercise about refactoring code to allow unrolling.
* **Advanced** Various exercises
    * **Exercise 1** about choosing to unroll inner or outer loop.
    * **Exercise 2** about balancing unroll factors
    * **Exercise 3** combining pipeline and unroll