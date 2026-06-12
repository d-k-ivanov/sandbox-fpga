1. This architecture applies pipeline to all loops and inlines all functions automatically.

2. Applying the pragma dataflow stops the inlining and reduces latency by around 25% while keeping area around the same.
```cpp
#include <stdint.h>

#define MAX_ITEMS 32

void compute_sorted(
        float ratio[MAX_ITEMS],
        float values_in[MAX_ITEMS],
        float weights_in[MAX_ITEMS],
        float values_sorted[MAX_ITEMS],
        float weights_sorted[MAX_ITEMS])
{
    // Copy inputs to sortable local arrays
    for(int i=0;i<MAX_ITEMS;i++){
        values_sorted[i]  = values_in[i];
        weights_sorted[i] = weights_in[i];
        ratio[i] = values_in[i] / weights_in[i];
    }

    // Selection sort descending
    for(int i = 0; i < MAX_ITEMS - 1; i++) {
        int max_index = i;
        for (int j = i + 1; j < MAX_ITEMS; j++) {
            if (ratio[j] > ratio[max_index])
                max_index = j;
        }

        // Swap ratio, values, weights
        float tr = ratio[max_index];
        ratio[max_index] = ratio[i];
        ratio[i] = tr;

        float tv = values_sorted[max_index];
        values_sorted[max_index] = values_sorted[i];
        values_sorted[i] = tv;

        float tw = weights_sorted[max_index];
        weights_sorted[max_index] = weights_sorted[i];
        weights_sorted[i] = tw;
    }
}

void pick_items_stage(
        float values_sorted[MAX_ITEMS],
        float weights_sorted[MAX_ITEMS],
        float capacity,
        float *total_value_out)
{
    float total = 0.0f;

pick_loop:
    for(int i=0;i<MAX_ITEMS;i++){
        float w = weights_sorted[i];
        float v = values_sorted[i];

        float take = (capacity > 0 && w <= capacity) ? 1.0f
                    : (capacity > 0 ? capacity/w : 0.0f);

        total += v * take;
        capacity -= w * take;
    }
    *total_value_out = total;
}

void fractional_knapsack(
        float weights[MAX_ITEMS],
        float values[MAX_ITEMS],
        float capacity,
        float *total_value)
{

    float ratio[MAX_ITEMS];
    float values_sorted[MAX_ITEMS];
    float weights_sorted[MAX_ITEMS];

    #pragma HLS DATAFLOW
    compute_sorted(ratio, values, weights, values_sorted, weights_sorted);
    pick_items_stage(values_sorted, weights_sorted, capacity, total_value);
}

```
3. By disabling pipeline we can make this design fully iterative,which reduces area but increments the number of cycles.However, throughput and area don't change much compared to baseline.
```cpp
#include <stdint.h>

#define MAX_ITEMS 32

void compute_sorted(
        float ratio[MAX_ITEMS],
        float values_in[MAX_ITEMS],
        float weights_in[MAX_ITEMS],
        float values_sorted[MAX_ITEMS],
        float weights_sorted[MAX_ITEMS])
{
    // Copy inputs to sortable local arrays
    for(int i=0;i<MAX_ITEMS;i++){
        #pragma HLS PIPELINE off
        values_sorted[i]  = values_in[i];
        weights_sorted[i] = weights_in[i];
        ratio[i] = values_in[i] / weights_in[i];
    }

    // Selection sort descending
    for(int i = 0; i < MAX_ITEMS - 1; i++) {
        int max_index = i;
        for (int j = i + 1; j < MAX_ITEMS; j++) {
            #pragma HLS PIPELINE off
            if (ratio[j] > ratio[max_index])
                max_index = j;
        }

        // Swap ratio, values, weights
        float tr = ratio[max_index];
        ratio[max_index] = ratio[i];
        ratio[i] = tr;

        float tv = values_sorted[max_index];
        values_sorted[max_index] = values_sorted[i];
        values_sorted[i] = tv;

        float tw = weights_sorted[max_index];
        weights_sorted[max_index] = weights_sorted[i];
        weights_sorted[i] = tw;
    }
}

void pick_items_stage(
        float values_sorted[MAX_ITEMS],
        float weights_sorted[MAX_ITEMS],
        float capacity,
        float *total_value_out)
{
    float total = 0.0f;

pick_loop:
    for(int i=0;i<MAX_ITEMS;i++){
        #pragma HLS PIPELINE off
        float w = weights_sorted[i];
        float v = values_sorted[i];

        float take = (capacity > 0 && w <= capacity) ? 1.0f
                    : (capacity > 0 ? capacity/w : 0.0f);

        total += v * take;
        capacity -= w * take;
    }
    *total_value_out = total;
}

void fractional_knapsack(
        float weights[MAX_ITEMS],
        float values[MAX_ITEMS],
        float capacity,
        float *total_value)
{

    float ratio[MAX_ITEMS];
    float values_sorted[MAX_ITEMS];
    float weights_sorted[MAX_ITEMS];


    compute_sorted(ratio, values, weights, values_sorted, weights_sorted);
    pick_items_stage(values_sorted, weights_sorted, capacity, total_value);
}
```
4. Because the main limiting factor for throughput is memory accesses we don't need to unroll any loops. By just partitioning memories by a factor of 2 we can achieve better throughput, but because many loops depend on a single variable that can't be partitioned we end up with bottlenecks that prevent us for increasing the throughput further.
```cpp
#include <stdint.h>

#define MAX_ITEMS 32

void compute_sorted(
        float ratio[MAX_ITEMS],
        float values_in[MAX_ITEMS],
        float weights_in[MAX_ITEMS],
        float values_sorted[MAX_ITEMS],
        float weights_sorted[MAX_ITEMS])
{
    // Copy inputs to sortable local arrays
    for(int i=0;i<MAX_ITEMS;i++){
        #pragma HLS PIPELINE II=1
        values_sorted[i]  = values_in[i];
        weights_sorted[i] = weights_in[i];
        ratio[i] = values_in[i] / weights_in[i];
    }

    // Selection sort descending
    for(int i = 0; i < MAX_ITEMS - 1; i++) {
        int max_index = i;
        for (int j = i + 1; j < MAX_ITEMS; j++) {
            #pragma HLS PIPELINE II=1
            if (ratio[j] > ratio[max_index])
                max_index = j;
        }

        // Swap ratio, values, weights
        float tr = ratio[max_index];
        ratio[max_index] = ratio[i];
        ratio[i] = tr;

        float tv = values_sorted[max_index];
        values_sorted[max_index] = values_sorted[i];
        values_sorted[i] = tv;

        float tw = weights_sorted[max_index];
        weights_sorted[max_index] = weights_sorted[i];
        weights_sorted[i] = tw;
    }
}

void pick_items_stage(
        float values_sorted[MAX_ITEMS],
        float weights_sorted[MAX_ITEMS],
        float capacity,
        float *total_value_out)
{
    float total = 0.0f;

pick_loop:
    for(int i=0;i<MAX_ITEMS;i++){
        #pragma HLS PIPELINE II=1
        float w = weights_sorted[i];
        float v = values_sorted[i];

        float take = (capacity > 0 && w <= capacity) ? 1.0f
                    : (capacity > 0 ? capacity/w : 0.0f);

        total += v * take;
        capacity -= w * take;
    }
    *total_value_out = total;
}

void datapath1(
        float weights[MAX_ITEMS],
        float values[MAX_ITEMS],
        float capacity,
        float *total_value)
{
#pragma HLS DATAFLOW 
#pragma HLS ARRAY_PARTITION variable=weights dim=1 type=complete
#pragma HLS ARRAY_PARTITION variable=values dim=1 type=complete
    float ratio[MAX_ITEMS];
    float values_sorted[MAX_ITEMS];
    float weights_sorted[MAX_ITEMS];


    compute_sorted(ratio, values, weights, values_sorted, weights_sorted);
    pick_items_stage(values_sorted, weights_sorted, capacity, total_value);
}

```


5.
| metric          | Baseline |Dataflow        | Fully Iterative | Latency Reduction(Parallelization) |
| --------------- | -------- |----------------|-----------------| ---------------------------------- |
| Latency(Cycles) |   3858       |  3149          |    4258             |        2187          |
| LUTs            |   1706       |       1829         |      1553           |      2099            |
| FFs             |  1423        |     1563           |      1302           |          3478        |
| DSPs            |  10        |    10            |   10              |              10    |
| BRAMs           |     4     |     4           |     4            |             4     |

The most efficient one is the Dataflow architecture, because it has the most balance between area and throughput. However, dependending on your objectives you may prefer the fully iterative or the latency reduction versions.