#include "sort_algorithms.h"
#include "dynamic_array.h"

/*
(Helper) helper function
Merge divided arrays 
*/
void integer_merge_sort_inplace_merge(DynArray* dynamic_array, SortResult* sort_result, const size_t left_index, const size_t middle_index, const size_t right_index) {
    //
    // Get length of both halfes
    size_t left_half_len = middle_index - left_index + 1;
    size_t right_half_len = right_index - middle_index;
    //
    // Create temporary buffers
    int left_temp_buff[left_half_len];
    int right_temp_buff[right_half_len];
    //
    // Copy left-half into left_temp_buf
    int* element;
    for (size_t i = 0; i < left_half_len; i++) {
        element = (int*)get_element_by_index(dynamic_array, left_index + i);
        if (element == NULL) {
            //
            // Couldn't get element from dynamic-array
            sort_result->error_code = NULL_PTR_ERROR;
            return;
        }
        left_temp_buff[i] = *element;
    }
    //
    // Copy right-half into right_temp_buf
    for (size_t j = 0; j < right_half_len; j++) {
        element = (int*)get_element_by_index(dynamic_array, middle_index + 1 + j);
        if (element == NULL) {
            //
            // Couldn't get element from dynamic-array
            sort_result->error_code = NULL_PTR_ERROR;
            return;
        }
        right_temp_buff[j] = *element;
    }
    //
    // Merge back into dynamic-array
    //
    // `i` index of left_temp_buff
    // `j` index of right_temp_buff
    // `k` index at actualy dynamic-array
    size_t i, j, k;
    i = 0; j = 0; k = left_index;
    while (i < left_half_len && j < right_half_len) {
        if (left_temp_buff[i] <= right_temp_buff[j]) {
            //
            // place left_temp_buff[i]
            if (replace_element_by_index(dynamic_array, k, (void*)&(left_temp_buff[i]), sizeof(int)) != NO_ERROR) {
                //
                // Couldn't replace element
                sort_result->error_code = NULL_PTR_ERROR;
                return;
            }
            i++;
        } else {
            //
            // place right_temp_buff[j]
            if (replace_element_by_index(dynamic_array, k, (void*)&(right_temp_buff[j]), sizeof(int)) != NO_ERROR) {
                //
                // Couldn't replace element
                sort_result->error_code = NULL_PTR_ERROR;
                return;
            }
            j++;
        }
        k++;
    }
    //
    // Copy remaining elements (only one side have leftovers)
    while (i < left_half_len) {
        if (replace_element_by_index(dynamic_array, k, (void*)&(left_temp_buff[i]), sizeof(int)) != NO_ERROR) {
            //
            // Couldn't replace element
            sort_result->error_code = NULL_PTR_ERROR;
            return;
        }
        i++;
        k++;
    }
    while (j < right_half_len) {
        if (replace_element_by_index(dynamic_array, k, (void*)&(right_temp_buff[j]), sizeof(int)) != NO_ERROR) {
            //
            // Couldn't replace element
            sort_result->error_code = NULL_PTR_ERROR;
            return;
        }
        j++;
        k++;
    }
}

/*
Helper function
Merge-Sort for dynamic-array with integer-elements.
*/
void integers_merge_sort_inplace(DynArray* dynamic_array, SortResult* sort_result, const size_t left_index, const size_t right_index) {
    if (left_index < right_index) {
        size_t middle_index = left_index + (right_index - left_index)/2;
        //
        // Sort first half
        integers_merge_sort_inplace(dynamic_array, sort_result, left_index, middle_index);
        //
        // Sort second half
        integers_merge_sort_inplace(dynamic_array, sort_result, middle_index+1, right_index);
        //
        // Merge sub-arrays
        integer_merge_sort_inplace_merge(dynamic_array, sort_result, left_index, middle_index, right_index);
    }
}

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
    size_t dyn_array_len = dynamic_array->length;
    //
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
}

/*
Sort integers-dynamic-array inplace with the given `Sort_Algorithm`.
This function assumes that **all** elements in the given dynamic-array are integers.
Returns `INVALID_ARRAY_ERROR` if data-size of element doesn't equal `sizeof(int)`.
*/
SortResult sort_dyn_array_integers_inplace(DynArray* dynamic_array, Sort_Algorithm sort_algorithm) {
    SortResult sort_result = {.error_code=NO_ERROR};
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
            integers_merge_sort_inplace(dynamic_array, &sort_result, 0, dynamic_array->length-1);
            break;
        
        default:
            //
            // Given `sort_algorithm` is invalid
            sort_result.error_code = INVALID_ARGUMENT_ERROR;
            break;
    }

    return sort_result;
}