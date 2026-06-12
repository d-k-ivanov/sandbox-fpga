# TASK
Add the #pragma HLS PIPELINE II=1 directive to pipeline the loop. Then run C synthesis in Vitis HLS for both the original and modified versions of the code.

Compare the following synthesis results:

Total latency (in clock cycles),Initiation interval (II),Resource usage (LUTs, FFs, DSPs) and maximum clock frequency. Use them to fill the following table.

> On xcu50-fsvh2104-2-e

## Finished table
| Metric                     | **Without Pipelining** | **With `#pragma HLS PIPELINE`** |
| -------------------------- | ---------------------- | ------------------------------- |
| **Total Latency (cycles)** | 4097                   | 1023                            |
| **LUTs Used**              | 303                    | 332                             |
| **FFs Used**               | 204                    | 269                             |
| **DSPs Used**              | 2                      | 2                               |
| **BRAMs Used**             | 0                      | 0                               |

