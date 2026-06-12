#define INPUT 256
#define VALUE 128

void histogram_map(int in[INPUT/2], int hist[VALUE]) {
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
void top_function(int inputA[INPUT/2], int inputB[INPUT/2], int hist[VALUE])
{
    int hist1[VALUE];
    int hist2[VALUE];
    histogram_map(inputA, hist1);
    histogram_map(inputB, hist2);
    histogram_reduce(hist1, hist2, hist);
}
 