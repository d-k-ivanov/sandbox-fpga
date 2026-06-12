# Internal Memory Use
Memory is a critical part of FPGA design. This section covers how to efficiently store and access data using local arrays, block RAM, and partitioning techniques. You'll learn how access patterns and array configurations directly affect performance and area.

## Index

* **4.1** Explaining the different memory types and how to define them
    * Exercise about defining different types of memory
* **4.2** Explaining array partition and how it can be used to increment throughput.
    * Exercise about partitioning a memory that is used in an unroll loop so that more data can be accesed at once.
* **4.3** Explaining array reshape and how it can save resources and increment throughput.
    * Exercise about reshaping to increment throughput
* **4.4** Explaining how to partition and reshape 2D arrays.
    * Exercise about partitioning the second dimention of a matrix.
* **Advanced** Various exercises
    * **Exercise 1** about partitioning and pipelining
    * **Exercise 2** comparing partition and reshape
    * **Exercise 3** choosing the correct factor when reshaping
