# What is INLINE?

Inlining is a technique in Vitis HLS that allows you to replace a function call with the actual body of the function. Normally, when you write a function in C and call it from another function, Vitis HLS will synthesize it as a separate block of hardware. Each call to that function requires extra control logic to handle entering and exiting the block, which can add overhead and prevent the tool from fully optimizing loops. By using the #pragma HLS INLINE directive, you tell Vitis HLS to merge the function directly into the caller. This eliminates the function call overhead and allows the operations inside the function to be optimized together with the calling code.

## Code examples

Here is a simple example where an addition function is used inside a loop.

```cpp
int add_element(int x) {
#pragma HLS inline off
    return x * 2;
}

void datapath1(int a[256], int b[256], int c[256]) {
    for (int i = 0; i < 256; i++) {
#pragma HLS UNROLL
        c[i] = add_element(b[i]) + a[i];
    }
}

```

In this sequential version, the tool creates a separate block of hardware for the add function.

If we inline the function, the addition becomes part of the loop itself:
```cpp
int add_element(int x) {
#pragma HLS inline 
    return x * 2;
}

void datapath1(int a[256], int b[256], int c[256]) {
    for (int i = 0; i < 256; i++) {
#pragma HLS UNROLL
        c[i] = add_element(b[i]) + a[i];
    }
}

```
| metric          | With Inline| Without Inline |
| --------------- | ---------------- | ------------- |
| Latency(Cycles) |     129      |       129    |
| LUTs            |      16097    |     6191       |
| FFs             | 8322            | 194          |
| BRAMs           | 0               | 0            |
| DSPs            | 0                | 0             |
With the INLINE directive, the function is no longer synthesized as a separate block. Instead, its body is inserted directly into the loop. 
## Why INLINE Matters

Inlining is important because in some cases it allows us to use hardware more efficiently in the calling function. However, if the parent function calls the inlined function multiple times area will increase.
## How to Use INLINE in Vitis

To inline a function, you place the #pragma HLS INLINE directive at the beginning of the function body. 
```cpp
int add(int x, int y) {
    #pragma HLS inline
    return x + y;
}
```
However, it is also possible to call the inline pragma from the top function:

```cpp
int add(int x, int y) {
    return x + y;
}

void top_function(int a[256], int b[256], int c[256]) {
    for (int i = 0; i < 256; i++) {
        #pragma HLS inline recursive
        c[i] = add(a[i], b[i]);
    }
}
```
```
Note: be careful, all pragmas inside the inlined function will be ignored.
```
and to turn it off:
```cpp
#pragma HLS inline off
```

This is useful because vitis automatically inlines small functions.
