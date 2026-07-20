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

    return NO_ERROR;
}

/*
Initialize a new dynamic-array.
*/
Error_Code init_dyn_array(DynArray* dynamic_array) {
    if (dynamic_array == NULL) {
        //
        // Given pointer is the NULL-pointer
        return NULL_PTR_ERROR;
    }
    
    dynamic_array->head_ptr = NULL;
    dynamic_array->tail_ptr = NULL;

    return NO_ERROR;
}

/*
(Helper) Helper function
Create node and copy memory data.
This function assumes, that the given `data-ptr` and `data_size` are valid.
*/
DynArrayNode* create_new_dyn_array_node(void* data, const size_t data_size) {
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
*/
Error_Code add_first_element_to_dyn_array(DynArray* dynamic_array, void* data, const size_t data_size) {
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

    return NO_ERROR;
}

/*
Append element to dynamic-array.
*/
Error_Code append_element_to_dyn_array(DynArray* dynamic_array, void* data, const size_t data_size) {
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
Get amount of elements in dynamic-array.
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
Error_Code append_static_array_elements_to_dyn_array(DynArray* dynamic_array, void* static_array, const size_t static_array_elem_size, const size_t static_array_len) {
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
Delete all elements on an dynamic-array.
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