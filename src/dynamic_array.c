#include "dynamic_array.h"
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>

/*
Helper function
Check whether provided DynArray-Pointer is pointing to a valid Dynamic-Array.
*/
Error_Code check_dyn_array(const DynArray* dynamic_array) {
    if (dynamic_array == NULL || (dynamic_array->head_ptr == NULL && dynamic_array->tail_ptr != NULL)
        || (dynamic_array->head_ptr != NULL && dynamic_array->tail_ptr == NULL)) {
        //
        // Given pointer is the NULL-pointer
        return NULL_PTR_ERROR;
    }
    //
    if ((dynamic_array->head_ptr == NULL && dynamic_array->length != 0) || 
        (dynamic_array->head_ptr != NULL && dynamic_array->length == 0)) {
        //
        // Dynamic-array is empty, but length-value is not 0
        // OR dynamic-array is not empty, but length-value is 0
        return INVALID_ARRAY_ERROR;
    }

    return NO_ERROR;
}

/*
Initialize a new dynamic-array.

Set `dynamic_array->length` to 0.
*/
Error_Code init_dyn_array(DynArray* dynamic_array) {
    if (dynamic_array == NULL) {
        //
        // Given pointer is the NULL-pointer
        return NULL_PTR_ERROR;
    }
    
    dynamic_array->head_ptr = NULL;
    dynamic_array->tail_ptr = NULL;
    dynamic_array->length = 0;

    return NO_ERROR;
}

/**
 * (Helper) Helper function -
 * Create node and copy memory data.
 * 
 * @param data A void-Pointer to the actual data that should be stored at the new `DynArrayNode`.
 * @param data_size Size in Bytes of the given data.
 * 
 * @return `DynArrayNode*`-Pointer on success; Otherwise `NULL`-Pointer
 * @note This function assumes,that the given `data`-pointer isn't the `NULL`-Pointer and `data_size` is not `0`.
 */
DynArrayNode* create_new_dyn_array_node(const void* data, const size_t data_size) {
    //
    // Allocate new `DynArrayNode`
    DynArrayNode* new_node = (DynArrayNode*) calloc(1, sizeof(DynArrayNode));
    if (new_node == NULL) {
        //
        // Allocation failed
        // NULL_PTR_ERROR
        return NULL;
    }
    //
    // Set next_ptr and prev_ptr to NULL
    new_node->next_ptr = NULL;
    new_node->prev_ptr = NULL;
    //
    // Set data_size-value
    new_node->data_size = data_size;
    //
    // Allocate actual data in node
    new_node->data = calloc(1, data_size);
    if (new_node->data == NULL) {
        //
        // Allocation failed
        // NULL_PTR_ERROR
        free(new_node);
        return NULL;
    }
    //
    // Copy data
    memcpy(new_node->data, data, data_size);
    //
    // NO_ERROR
    return new_node;
}

/*
Helper function
Add first element to dynamic-array.
This function assumes, that the given dynamic-array has already been checked with `check_dyn_array` and that the given
`data-ptr` and `data_size` are also valid.

Set `dynamic_array->length` to 1.
*/
Error_Code add_first_element_to_dyn_array(DynArray* dynamic_array, const void* data, const size_t data_size) {
    DynArrayNode* first_node = create_new_dyn_array_node(data, data_size);
    if (first_node == NULL) {
        //
        // Failed to create new node
        return NULL_PTR_ERROR;
    }
    //
    // Set head-ptr and tail_ptr to first_node
    dynamic_array->head_ptr = first_node;
    dynamic_array->tail_ptr = first_node;
    //
    // Set length-counter of dynamic-array to 1
    dynamic_array->length = 1;

    return NO_ERROR;
}

/*
Append element to dynamic-array.

Increases `dynamic_array->length` by 1.
*/
Error_Code append_element_to_dyn_array(DynArray* dynamic_array, const void* data, const size_t data_size) {
    if (check_dyn_array(dynamic_array) != NO_ERROR) {
        //
        // Given dynamic-array is invalid
        return INVALID_ARRAY_ERROR;
    }
    //
    // Check whether given data-size is valid
    if (data_size == 0) {
        //
        // data_size shouldn't be zero
        return INVALID_DATA_SIZE;
    }
    //
    // Check whether given data-pointer is probably valid
    if (data == NULL) {
        //
        // data-pointer shouldn't be the NULL-pointer
        return NULL_PTR_ERROR;
    }
    //
    // Check size of array
    if (dynamic_array->head_ptr == dynamic_array->tail_ptr) {
        //
        // Array has one element or none
        if (dynamic_array->head_ptr == NULL) {
            //
            // Because of the 'check_dyn_array'-func we can now presuppose 
            // that the tail_ptr is also the NULL-ptr
            // Array is empty -> Given data is first element
            return add_first_element_to_dyn_array(dynamic_array, data, data_size);
        }
        //
        // Given array has one element
        // We can proceed with normal 'append'-function
    }
    //
    // Create new node
    DynArrayNode* new_node = create_new_dyn_array_node(data, data_size);
    if (new_node == NULL) {
        //
        // Failed to create new node
        return NULL_PTR_ERROR;
    }
    //
    // Append new_node to array
    // Leave `new_node->next_ptr` as NULL
    new_node->prev_ptr = dynamic_array->tail_ptr;
    dynamic_array->tail_ptr->next_ptr = new_node;
    dynamic_array->tail_ptr = new_node;
    //
    // Increase length-counter of dynamic-array
    dynamic_array->length++;

    return NO_ERROR;
}

/*
Get and Return last element of dynamic-array.
Returns 'NULL`-ptr if empty or an error occured.
*/
void* get_last(const DynArray* dynamic_array) {
    if (check_dyn_array(dynamic_array) != NO_ERROR) {
        //
        // Given dynamic-array is invalid
        return NULL;
    }
    //
    if (dynamic_array->tail_ptr == NULL) {
        //
        // Array is empty
        return NULL;
    }
    //
    return dynamic_array->tail_ptr->data;
}

/*
Get and Return first element of dynamic-array.
Returns 'NULL`-ptr if empty or an error occured.
*/
void* get_first(const DynArray* dynamic_array) {
    if (check_dyn_array(dynamic_array) != NO_ERROR) {
        //
        // Given dynamic-array is invalid
        return NULL;
    }
    //
    if (dynamic_array->head_ptr == NULL) {
        //
        // Array is empty
        return NULL;
    }
    //
    return dynamic_array->head_ptr->data;
}

/*
Get amount of elements in dynamic-array by iterating through whole dynamic-array.
Boolean indicates whether an error occured or the given dynamic-array is invalid.
*/
bool get_len(const DynArray* dynamic_array, size_t* len) {
    if (check_dyn_array(dynamic_array) != NO_ERROR) {
        //
        // Given dynamic-array is invalid
        return false;
    }
    //
    if (len == NULL) {
        //
        // Given len-ptr is the NULL-ptr
        return false;
    }
    DynArrayNode* current_ptr = dynamic_array->head_ptr;
    *len = 0;
    while (current_ptr != NULL) {
        (*len)++;
        current_ptr = current_ptr->next_ptr;
    }
    return true;
}

/*
Copy the array’s elements individually into the dynamic-array.
Uses `append_element_to_dyn_array` under the hood.
*/
Error_Code append_static_array_elements_to_dyn_array(DynArray* dynamic_array, const void* static_array, const size_t static_array_elem_size, const size_t static_array_len) {
    if (check_dyn_array(dynamic_array) != NO_ERROR) {
        //
        // Given dynamic-array is invalid
        return INVALID_ARRAY_ERROR;
    }
    //
    // Check whether given static_array_element-size is valid
    if (static_array_elem_size == 0 || static_array_len == 0) {
        //
        // data_size shouldn't be zero
        return INVALID_DATA_SIZE;
    }
    //
    // Check whether given static_array-pointer is probably valid
    if (static_array == NULL) {
        //
        // data-pointer shouldn't be the NULL-pointer
        return NULL_PTR_ERROR;
    }
    //
    Error_Code append_elem_error_code = NO_ERROR;
    for (size_t elem_counter = 0; elem_counter < static_array_len; elem_counter++) {
        append_elem_error_code = append_element_to_dyn_array(dynamic_array, static_array+(elem_counter*static_array_elem_size), static_array_elem_size);
        if (append_elem_error_code != NO_ERROR) {
            break;
        }
    }

    return append_elem_error_code;
}

/*
Get element-ptr of dynamic-array-Node by index.

Return `NULL` if an error occurs.
*/
DynArrayNode* get_element_ptr_by_index(const DynArray* dynamic_array, const size_t index) {
    if (check_dyn_array(dynamic_array) != NO_ERROR) {
        //
        // Given dynamic-array is invalid
        return NULL;
    }
    //
    // Check whether given index is valid
    size_t array_len = dynamic_array->length;
    if (index >= array_len) {
        //
        // Given dynamic-array index is out of bounds
        return NULL;
    }
    //
    // Check whether dynamic-array is empty
    if (array_len == 0) {
        //
        // Nothing to do since there is no element to get
        return NULL;
    }
    //
    // Decide whether to iterate dynamic-array from tail or head
    DynArrayNode* current_ptr = dynamic_array->head_ptr;
    bool from_head = true;
    if (array_len >= 10 && (index >= array_len/2)) {
        current_ptr = dynamic_array->tail_ptr;
        from_head = false;
    }
    //
    // Iterate through dynamic-array
    size_t index_counter = 0;
    if (!from_head) {
        //
        // `array_len-1` is allowed, because we already 
        // checked if the dynamic-array is empty
        index_counter = array_len-1;
    }
    while (current_ptr != NULL && index_counter != index) {
        if (from_head) {
            current_ptr = current_ptr->next_ptr;
            index_counter++;
        } else {
            current_ptr = current_ptr->prev_ptr;
            index_counter--;
        }
    }
    if (current_ptr == NULL) {
        //
        // Shouldn't be accessible, since Index is valid
        // TODO: called by any edge case?
        return NULL;
    }
    return current_ptr;
}

/*
Get element of dynamic-array by index.

Return `NULL`-ptr if an error occurs.
*/
void* get_element_by_index(const DynArray* dynamic_array, const size_t index) {
    DynArrayNode* current_ptr = get_element_ptr_by_index(dynamic_array, index);
    if (current_ptr == NULL) {
        return NULL;
    }
    return current_ptr->data;
}

/*
Append elements of dynamic-array `b` to dynamic-array `a`.
Uses `append_element_to_dyn_array` under the hood.
*/
bool append_dyn_arrays_inplace(DynArray* a, const DynArray* b) {
    DynArray* dyn_array_a = a;
    const DynArray* dyn_array_b = b;
    //
    // Check both dynamic-arrays
    if (check_dyn_array(dyn_array_a) != NO_ERROR || check_dyn_array(dyn_array_b) != NO_ERROR) {
        //
        // One or both of the given dynamic-arrays are invalid
        // INVALID_ARRAY_ERROR
        return false;
    }
    if (dyn_array_b->length == 0) {
        //
        // Dynamic-array `b` is empty, nothing to append
        // NO_ERROR
        return true;
    }
    //
    // Iterate through dynamic-array `b`
    Error_Code append_elem_error_code = NO_ERROR;
    DynArrayNode* current_b_ptr = dyn_array_b->head_ptr;
    while (current_b_ptr != NULL) {
        append_elem_error_code = append_element_to_dyn_array(dyn_array_a, current_b_ptr->data, current_b_ptr->data_size);
        if (append_elem_error_code != NO_ERROR) {
            //
            // Appending element went wrong
            return false;
        }
        current_b_ptr = current_b_ptr->next_ptr;
    }
    //
    // NO_ERROR
    return true;
}

/*
Swap position of elements by its indices.
*/
Error_Code swap_elements_by_indices(DynArray* dynamic_array, const size_t index_a, const size_t index_b) {
    if (check_dyn_array(dynamic_array) != NO_ERROR) {
        //
        // Given dynamic-array is invalid
        return INVALID_ARRAY_ERROR;
    }
    //
    // Check whether given indices are valid
    if (index_a >= dynamic_array->length || index_b >= dynamic_array->length) {
        //
        // One or both indices are invalid
        return INVALID_INDEX_ERROR;
    }
    //
    // Early exit when both are equal
    if (index_a == index_b) {
        //
        // Got equal indices. Nothing to swap.
        return NO_ERROR;
    }
    //
    // Get elements by indices
    DynArrayNode* element_a_ptr = get_element_ptr_by_index(dynamic_array, index_a);
    DynArrayNode* element_b_ptr = get_element_ptr_by_index(dynamic_array, index_b);
    if (element_a_ptr == NULL || element_b_ptr == NULL) {
        //
        // Couldn't get element-ptr
        return NULL_PTR_ERROR;
    }
    //
    // Swap elements by adjusting next_ptr and prev_ptr
    DynArrayNode* original_a_prev_ptr = element_a_ptr->prev_ptr;
    DynArrayNode* original_a_next_ptr = element_a_ptr->next_ptr;
    DynArrayNode* original_b_prev_ptr = element_b_ptr->prev_ptr;
    DynArrayNode* original_b_next_ptr = element_b_ptr->next_ptr;
    
    if (index_a < index_b) {
        //
        // A is on the left side of B
        if (original_a_next_ptr == element_b_ptr) {
            //
            // A is directly besides B
            if (element_a_ptr->prev_ptr != NULL) {
                element_a_ptr->prev_ptr->next_ptr = element_b_ptr;
            }
            element_a_ptr->prev_ptr = element_b_ptr;
            element_a_ptr->next_ptr = element_b_ptr->next_ptr;

            if (element_b_ptr->next_ptr != NULL) {
                element_b_ptr->next_ptr->prev_ptr = element_a_ptr;
            }
            element_b_ptr->prev_ptr = original_a_prev_ptr;
            element_b_ptr->next_ptr = element_a_ptr;
        } else {
            //
            // A is not directly besides B
            if (element_a_ptr->prev_ptr != NULL) {
                element_a_ptr->prev_ptr->next_ptr = element_b_ptr;
            }
            element_a_ptr->next_ptr->prev_ptr = element_b_ptr;
            element_a_ptr->prev_ptr = element_b_ptr->prev_ptr;
            element_a_ptr->next_ptr = element_b_ptr->next_ptr;
            
            if (element_b_ptr->next_ptr != NULL) {
                element_b_ptr->next_ptr->prev_ptr = element_a_ptr;
            }
            element_b_ptr->prev_ptr->next_ptr = element_a_ptr;
            element_b_ptr->prev_ptr = original_a_prev_ptr;
            element_b_ptr->next_ptr = original_a_next_ptr;
        }
    } else {
        //
        // index_a > index_b
        //
        // B is on the left side of A
        if (original_b_next_ptr == element_a_ptr) {
            //
            // A is directly besides B
            if (element_b_ptr->prev_ptr != NULL) {
                element_b_ptr->prev_ptr->next_ptr = element_a_ptr;
            }
            element_b_ptr->prev_ptr = element_a_ptr;
            element_b_ptr->next_ptr = element_a_ptr->next_ptr;

            if (element_a_ptr->next_ptr != NULL) {
                element_a_ptr->next_ptr->prev_ptr = element_b_ptr;
            }
            element_a_ptr->prev_ptr = original_b_prev_ptr;
            element_a_ptr->next_ptr = element_b_ptr;
        } else {
            //
            // A is not directly besides B
            if (element_b_ptr->prev_ptr != NULL) {
                element_b_ptr->prev_ptr->next_ptr = element_a_ptr;
            }
            element_b_ptr->next_ptr->prev_ptr = element_a_ptr;
            element_b_ptr->prev_ptr = element_a_ptr->prev_ptr;
            element_b_ptr->next_ptr = element_a_ptr->next_ptr;
            
            if (element_a_ptr->next_ptr != NULL) {
                element_a_ptr->next_ptr->prev_ptr = element_b_ptr;
            }
            element_a_ptr->prev_ptr->next_ptr = element_b_ptr;
            element_a_ptr->prev_ptr = original_b_prev_ptr;
            element_a_ptr->next_ptr = original_b_next_ptr;
        }
    }
    //
    // Adjust head_ptr/tail_ptr if required
    if (element_a_ptr == dynamic_array->head_ptr) {
        //
        // element_b_ptr is the new head_ptr
        dynamic_array->head_ptr = element_b_ptr;

    } else if (element_b_ptr == dynamic_array->head_ptr) {
        //
        // element_a_ptr is the new head_ptr
        dynamic_array->head_ptr = element_a_ptr;
    }
    if (element_a_ptr == dynamic_array->tail_ptr) {
        //
        // element_b_ptr is the new tail_ptr
        dynamic_array->tail_ptr = element_b_ptr;

    } else if (element_b_ptr == dynamic_array->tail_ptr) {
        //
        // element_a_ptr is the new tail_ptr
        dynamic_array->tail_ptr = element_a_ptr;
    }

    return NO_ERROR;
}

/*
Replace an element-data by its index inplace.
Stored element-data gets deleted and new element-data gets stored at the given index.
*/
Error_Code replace_element_by_index(DynArray* dynamic_array, const size_t index, const void* data, const size_t data_size) {
    if (check_dyn_array(dynamic_array) != NO_ERROR) {
        //
        // Given dynamic-array is invalid
        return INVALID_ARRAY_ERROR;
    }
    //
    // Check whether given data-size is valid
    if (data_size == 0) {
        //
        // data_size shouldn't be zero
        return INVALID_DATA_SIZE;
    }
    //
    // Check whether given data-pointer is probably valid
    if (data == NULL) {
        //
        // data-pointer shouldn't be the NULL-pointer
        return NULL_PTR_ERROR;
    }
    //
    // Check whether an element exists at the given index
    DynArrayNode* element_node_ptr = get_element_ptr_by_index(dynamic_array, index);
    if (element_node_ptr == NULL) {
        //
        // Index out of bounds
        return INVALID_INDEX_ERROR;
    }
    //
    // Check whether data-size is the same
    // Otherwise we have to deallocate space and allocate (new) space for the data
    if (element_node_ptr->data_size != data_size) {
        void* new_data_ptr = calloc(1, data_size);
        if (element_node_ptr->data == NULL) {
            //
            // Couldn't allocate space for new data
            return NULL_PTR_ERROR;
        }
        //
        // Deallocate current-data
        free(element_node_ptr->data);
        //
        // Set new data-ptr
        element_node_ptr->data = new_data_ptr;
    }
    //
    // Copy/Overwrite data
    memcpy(element_node_ptr->data, data, data_size);
    
    return NO_ERROR;
}

/**
 * Insert an element at the given index.
 * 
 * @param dynamic_array `DynArray`-Pointer to the given exsiting dynamic-array.
 * @param index The given where the new element should be inserted at.
 * @param data The `void`-Pointer to the data that should be stored at the new element.
 * @param data_size Size in Bytes of the given data.
 * 
 * @return `Error_Code` - `NO_ERROR` on success; otherwise another `Error_Code`.
 */
Error_Code insert_element_at_index(DynArray* dynamic_array, const size_t index, const void* data, const size_t data_size) {
    if (check_dyn_array(dynamic_array) != NO_ERROR) {
        //
        // Given dynamic-array is invalid
        return INVALID_ARRAY_ERROR;
    }
    //
    // Check whether given data-size is valid
    if (data_size == 0) {
        //
        // data_size shouldn't be zero
        return INVALID_DATA_SIZE;
    }
    //
    // Check whether given data-pointer is probably valid
    if (data == NULL) {
        //
        // data-pointer shouldn't be the NULL-pointer
        return NULL_PTR_ERROR;
    }
    //
    // Check whether given index are valid
    if (index >= dynamic_array->length) {
        //
        // Given index is out of bounds
        return INVALID_INDEX_ERROR;
    }
    //
    // Get element-ptr at given index
    DynArrayNode* current_node_at_index = get_element_ptr_by_index(dynamic_array, index);
    if (current_node_at_index == NULL) {
        //
        // Couldn't get element at the given index
        return NULL_PTR_ERROR;
    }
    //
    // Create new node
    DynArrayNode* new_node = create_new_dyn_array_node(data, data_size);
    if (new_node == NULL) {
        //
        // Couldn't create new node
        return NULL_PTR_ERROR;
    }
    //
    // Adjust next-pointer of new-node to current-node at index
    new_node->next_ptr = current_node_at_index;
    //
    // Adjust previous-pointer of new-node to previous-pointer of
    // current-node at index
    new_node->prev_ptr = current_node_at_index->prev_ptr;
    //
    // Adjust next-pointer of element previous to the current-node
    // at index to point at new-node
    if (current_node_at_index->prev_ptr != NULL) {
        current_node_at_index->prev_ptr->next_ptr = new_node;
    }
    //
    // Adjust previous-pointer of current-node at index to point at new-node
    current_node_at_index->prev_ptr = new_node;
    //
    // Adjust head_ptr if required
    if (current_node_at_index == dynamic_array->head_ptr) {
        //
        // New node gets new head_ptr
        dynamic_array->head_ptr = new_node;
    }
    //
    // Increase dynamic-array length-counter
    dynamic_array->length++;
    return NO_ERROR;
}

/*
Deallocate space of all elments in a dynamic-array.
*/
Error_Code clear_dyn_array(DynArray* dynamic_array) {
    if (check_dyn_array(dynamic_array) != NO_ERROR) {
        //
        // Given dynamic-array is invalid
        return INVALID_ARRAY_ERROR;
    }
    DynArrayNode* current_ptr = dynamic_array->head_ptr;
    //
    // Check if array is empty
    if (current_ptr == NULL) {
        //
        // Array is empty; nothing to deallocate
        return NO_ERROR;
    }
    while (current_ptr->next_ptr != NULL) {
        current_ptr = current_ptr->next_ptr;
        //
        // First deallocate data
        free(current_ptr->prev_ptr->data);
        //
        // Then deallocate node
        free(current_ptr->prev_ptr);
    }
    //
    // Deallocate data of head-ptr
    free(dynamic_array->tail_ptr->data);
    free(dynamic_array->tail_ptr);
    //
    // Re-initialize array
    return init_dyn_array(dynamic_array);
}