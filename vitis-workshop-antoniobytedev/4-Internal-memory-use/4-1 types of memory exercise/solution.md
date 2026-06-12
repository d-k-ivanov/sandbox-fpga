# Solution
```cpp
void datapath1(int A[512])
{
    int B[512];
    int C[512];
}
```
Despite this being the correct way to define them Vitis will realize that the arrays B and C aren't being used and will not assign any brams to them. To make vitis assign bram it's necessary to assign values to them and use them in a different cycle than in the one they are assigned.
```cpp
void top_function(int A[512],int &output)
{
    int B[512];
    int C[512];
    for(int i=0;i<512;i++)
    {
        B[i]=A[i];
        C[i]=A[i];
    }
    for(int i=0;i<512;i++)
    {
        output+=B[i]+C[511-i];
    }
}
```
It is also mandatory to have an output variable or vitis won't use any resource for the FPGA.