# TASK
Synthesize the code 3 times, one without pipeline, one using only pipeline and one using pipeline and the pragma hls dependency. Explain why we get a violation using pipeline only and show where it happens.

## Finished table
| Metric                        | **Without Pipelining** | **With `#pragma HLS PIPELINE`** | **Pipelined and Fixed Dependency** |
| ----------------------------- | ---------------------- | ------------------------------- | ---------------------------------- |
| **Total Latency (cycles)**    |                        |                                 |                                    |
| **LUTs Used**                 |                        |                                 |                                    |
| **FFs Used**                  |                        |                                 |                                    |
| **DSPs Used**                 |                        |                                 |                                    |
| **BRAMs Used**                |                        |                                 |                                    |