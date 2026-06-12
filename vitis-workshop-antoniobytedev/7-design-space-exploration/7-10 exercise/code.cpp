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


    compute_sorted(ratio, values, weights, values_sorted, weights_sorted);
    pick_items_stage(values_sorted, weights_sorted, capacity, total_value);
}
