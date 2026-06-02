#include "algorithms.h"
int binary_search_process(Process arr[], int low, int high, int target_pid) {
    while (low <= high) {
        int mid = low + (high - low) / 2; 
        if (arr[mid].pid == target_pid)
            return mid;
        if (arr[mid].pid < target_pid)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1; 
}
