# Solution
```cpp
#define INPUT 256
#define VALUE 128

void histogram_map(int in[INPUT/2], int hist[VALUE]) {
#pragma HLS DEPENDENCE variable=hist intra RAW false
    for(int i = 0; i < VALUE; i++) {
        #pragma HLS PIPELINE II=1
        hist[i] = 0;
    }
    int old = in[0];
    int acc = 0;
    for(int i = 0; i < INPUT/2; i++) {
        #pragma HLS PIPELINE II=1
        int val = in[i];
        if(old == val) {
            acc = acc + 1;
        }else{
            hist[old] = acc;
            acc = hist[val] + 1;
        }
        old = val;
    }  
    hist[old] = acc;
 }

void histogram_reduce(int hist1[VALUE], int hist2[VALUE], int output[VALUE]) {
    for(int i = 0; i < VALUE; i++) {
        #pragma HLS PIPELINE II=1
        output[i] = hist1[i] + hist2[i];
    }
}
 //Top level function
void datapath1(int inputA[INPUT/2], int inputB[INPUT/2], int hist[VALUE])
{
    #pragma HLS DATAFLOW
    int hist1[VALUE];
    int hist2[VALUE];
    histogram_map(inputA, hist1);
    histogram_map(inputB, hist2);
    histogram_reduce(hist1, hist2, hist);
}
 
```
By using the dataflow pragma we can reduce latency by a 100 cycles while maintaining a similar area. This showcases the importance of dataflow when working with sub functions.
# Finished table
| Metric                        | **Without DATAFLOW** | **With DATAFLOW** 
| ----------------------------- | ---------------------- | ------------------------------- | 
| **Total Latency (cycles)**    |         527           |          394                       |                                    |
| **LUTs Used**                 |       913                |       965                          |                                    |
| **FFs Used**                  |       397                |     401                            |                                    |
| **BRAMs Used**                  |     2                 |        2                        |                                    |
| **DSPUsed**                  |         0              |            0               |                                    |