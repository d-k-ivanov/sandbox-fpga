# Problems in pipelining -  False dependencies on conditional branches
When dealing with loops in vitis HLS we may come across a false dependency. A false dependency occurs when vitis believes a location can be accessed twice on the same cycle but in reality they are in different branches of the condicional. For example, let's run this code from vitis documentation.

```cpp
#define INPUT_SIZE 256
#define VALUE_SIZE 256
void histogram(int in[INPUT_SIZE], int hist[VALUE_SIZE]) {
 int acc = 0;
 int i, val;
 int old = in[0];
 false_dependency_loop: for(i = 0; i < INPUT_SIZE; i++)
 {
 #pragma HLS PIPELINE II=1
 val = in[i];
 if(old == val)
 {
 acc = acc + 1;
 }
 else
 {
 hist[old] = acc;
 acc = hist[val] + 1;
 }

 old = val;
 }

 hist[old] = acc;
}
```
In this example we get a II=2 pipeline as vitis believes the same address is being accessed in hist[val] and hist[old], but we know this is impossible due to the if statement.

![False dependency example](../../resources/ii%20violation%20branching.png)

## The solution


```cpp
 #pragma HLS DEPENDENCE variable=hist intra RAW false
```
We are only going to look into intra dependencies in this tutorial. This indicates that loop dependencies are within the same cycle.

RAW, WAR and WAW are relevant to intra dependencies only.

* RAW (Read-After-Write - true dependence)
The write instruction uses a value used by the read instruction.
* WAR (Write-After-Read - anti dependence)
The read instruction gets a value that is overwritten by the write instruction.
* WAW (Write-After-Write - output dependence)
Two write instructions write to the same location, in a certain order.

And by using false we declare that there is not actually a dependency between the variables.

By using the follwing pragma we can achieve II=1
```cpp
void histogram(int in[INPUT SIZE], int hist[VALUE SIZE]) {
 int acc = 0;
 int i, val;
 int old = in[0];
 #pragma HLS DEPENDENCE variable=hist intra RAW dependent=false
false_dependency_loop: for(i = 0; i < INPUT SIZE; i++)
 {
 #pragma HLS PIPELINE II=1
 val = in[i];
 if(old == val)
 {
 acc = acc + 1;
 }
 else
 {
 hist[old] = acc;
 acc = hist[val] + 1;
 }

 old = val;
 }

 hist[old] = acc;
}
```
![False dependency example](../../resources/falsedepenfixed.png)


As we can see by fixing the false dependency problem we can achieve double the throughput, so it's important to know which dependencies are false and which can be removed.