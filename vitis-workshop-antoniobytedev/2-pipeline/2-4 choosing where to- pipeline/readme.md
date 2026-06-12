# Problems in pipelining: choosing where to pipeline
It is important to be careful when choosing where to place the pipeline directive, as vitis has some hidden interactions that can be counter intuitive.

Consider the following code:

### Example 1

First, let's take a look at the code with no optimizations.
We need to add pipeline off as vitis tries to pipeline automatically.
```cpp
void datapath1(int a[256], int c[256])
{ 
    for (int i = 0; i < 256; i++) {
       #pragma HLS PIPELINE off
        c[i]= a[i]*4;
    }
}
```
![Cycles with pipeline](../../resources/no%20pipeline%20.png)
Here we can see that it needs 513 cycles to finish execution, this is because each loop iteration needs 2 cycles and 1 cycle its used for initialization. 

### Example 2
Now let's take a look at the same code but with pipeline inside the loop. This makes the processor schedule the operations so that it can start a new iteration of the loop every cycle.

```cpp
void datapath2(int a[256], int c[256])
{ 
    for (int i = 0; i < 256; i++) {
       #pragma HLS PIPELINE II=1
        c[i]= a[i]*4;
    }
}
```
![Cycles with pipeline](../../resources/pipeline%20interno.png)

Here we can see that even though we double the throughput the area doesn't increase much.

### Example 3
Now let's take a look at this example where we place the pipeline directive outside the loop.
```cpp
void datapath3(int a[256], int c[256])
{ 
    #pragma HLS PIPELINE II=1
    for (int i = 0; i < 256; i++) {
        c[i]= a[i]*4;
    }
}
```
![Cycles with pipeline](../../resources/pipeline%20fuera.png)
Looking at the data we can see that the throughput has doubled again but the area has increased exponentially.

**When placing the pipeline directive above a loop it unrolls it completely without stating it explicitly** and this also applies to nested loops. This is the reason we get 128 as the only limiting factor is the number of ports in the memory storing a.

Note that the mentioned method will even ignore the unroll off directive so be careful.
