#define _POSIX_C_SOURCE 200809L
#include <time.h>
#include "sort_algorithms.h"
#include "dynamic_array.h"
#include <stdio.h>

/*
Helper function
Bubble-Sort for dynamic-array with integer-elements
*/
void integers_bubble_sort_inplace(DynArray* dynamic_array, SortResult* sort_result) {
    bool swapped;
    int current_element, next_element;
    void* current_element_ptr;
    void* next_element_ptr;
    Error_Code swap_error_code;
    struct timespec start, end;
    size_t dyn_array_len = dynamic_array->length;
    //
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (size_t array_passes_counter = 0; array_passes_counter < dyn_array_len-1; array_passes_counter++) {
        swapped = false;
        for (size_t current_index = 0; current_index < dyn_array_len-array_passes_counter-1; current_index++) {
            //
            // Get current element
            current_element_ptr = get_element_by_index(dynamic_array, current_index);
            if (current_element_ptr == NULL) {
                sort_result->error_code = NULL_PTR_ERROR;
                break;
            }
            current_element = *(int*)current_element_ptr;
            //
            // Get next element
            next_element_ptr = get_element_by_index(dynamic_array, current_index+1);
            if (next_element_ptr == NULL) {
                sort_result->error_code = NULL_PTR_ERROR;
                break;
            }
            next_element = *(int*)next_element_ptr;
            //
            // Compare current_element and next_element
            if (current_element > next_element) {
                //
                // Swap current_element with new_element since current_element is larger
                swap_error_code = swap_elements_by_indices(dynamic_array, current_index, current_index+1);
                if (swap_error_code != NO_ERROR) {
                    //
                    // Swap failed
                    sort_result->error_code = swap_error_code;
                    break;
                }
                swapped = true;
            }
        }
        if (swapped == false) {
            break;
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    //
    // Calculate timedelta
    sort_result->runtime_ms = (double)(((end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec))/1e7);
}

/*
Sort integers-dynamic-array inplace with the given `Sort_Algorithm`.
This function assumes that **all** elements in the given dynamic-array are integers.
Returns `INVALID_ARRAY_ERROR` if data-size of element doesn't equal `sizeof(int)`.
*/
SortResult sort_dyn_array_integers_inplace(DynArray* dynamic_array, Sort_Algorithm sort_algorithm) {
    SortResult sort_result = {.error_code=NO_ERROR, .runtime_ms=-1.0};
    //
    if (check_dyn_array(dynamic_array) != NO_ERROR) {
        //
        // Given dynamic-array is invalid
        sort_result.error_code = INVALID_ARRAY_ERROR;
        return sort_result;
    }
    if (dynamic_array->length < 2) {
        //
        // Given dynamic-array has only one element or none
        sort_result.error_code = INVALID_ARRAY_ERROR;
        return sort_result;
    }
    //
    // Check whether the given array only has integers as elements
    size_t required_data_size = sizeof(int);
    DynArrayNode* current_ptr = dynamic_array->head_ptr;
    while (current_ptr != NULL) {
        if (current_ptr->data_size != required_data_size) {
            //
            // Given element is not an integer
            sort_result.error_code = INVALID_ARRAY_ERROR;
            return sort_result;
        }
        current_ptr = current_ptr->next_ptr;
    }
    //
    // Assuming all elements are integers
    // TODO: not foolproof - user has responsibility
    //
    // Calling actual sort-algorithm-function
    switch (sort_algorithm) {
        case SORT_ALG_BUBBLE:
            //
            // selected bubble-sort
            integers_bubble_sort_inplace(dynamic_array, &sort_result);
            break;
        
        case SORT_ALG_MERGE:
            //
            // selected merge-sort
            break;
        
        case SORT_ALG_QUICK:
            //
            // selected quick-sort
            break;
    }

    return sort_result;
}