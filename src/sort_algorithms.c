#include "sort_algorithms.h"
#include "dynamic_array.h"

/*
Helper function
Bubble-Sort for dynamic-array with integer-elements
*/


/*
Sort integers-dynamic-array inplace with the given `Sort_Algorithm`.
This function assumes that **all** elements in the given dynamic-array are integers.
Returns `INVALID_ARRAY_ERROR` if data-size of element doesn't equal `sizeof(int)`.
*/
SortResult sort_dyn_array_integers_inplace(DynArray* dynamic_array, Sort_Algorithm sort_algorithm) {
    SortResult sort_result = {NO_ERROR, -1};
    //
    if (check_dyn_array(dynamic_array) != NO_ERROR) {
        //
        // Given dynamic-array is invalid
        sort_result.error_code = INVALID_ARRAY_ERROR;
        return sort_result;
    }
    if (dynamic_array->length == 0) {
        //
        // Given dynamic-array is empty
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