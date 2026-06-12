# Loop optimization
Loop behavior drives hardware structure. In this section, we dive into loop flattening, fusion, tripcount specification, and managing dependencies. You'll learn to restructure loops not just for speed, but to better control synthesis results and resource balance.

## Index

* **5.1** Explaining the different types of loops and its differences.
    * Exercise about identifying different types of loops and refactoring to change its type.
* **5.2** Explaining loop merging and how it can save cycles and resources.
    * Exercise about merging a nested loop with a non nested one.
* **5.3** Explaining loop flattening and how it can reduce area and increase throughput.
    * Exercise about modifying the code that prevents flattening.
* **Advanced** Various exercises
    * **Exercise 1** about interactions between merging and flattening
    * **Exercise 2** about dependencies when merging loops
    * **Exercise 3** about merging only specific loops