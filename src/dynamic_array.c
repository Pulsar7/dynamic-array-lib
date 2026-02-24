#include <stdlib.h>
#include <string.h>
//
#include "dynamic_array.h"
#include "constants.h"

/*
Initialize head-pointer and tail-pointer of array.

Returns `ERROR_CODE`:
    - `NOERROR`: Array has been successfully initialized.
    - `NULL_PTR_ERROR`: Given array is NULL
*/
ERROR_CODE init_array(DynamicArray* array) {
    if (array == NULL) {
        return NULL_PTR_ERROR;
    }

    array->head_ptr = NULL;
    array->tail_ptr = NULL;

    return NOERROR;
}

/*
Helper function, to check if the given dynamic-array is invalid.

Returns `ERROR_CODE`:
    - `NOERROR`: Element has been sucessfully appended to the dynamic-array
    - `INVALID_ARRAY_ERROR`: Given dynamic-array is invalid (missing or invalid `head_ptr` and `tail_ptr`)
*/
ERROR_CODE if_invalid_dynamic_array(DynamicArray* array) {
    if (array == NULL) {
        return INVALID_ARRAY_ERROR;
    } else if ((array->head_ptr == NULL && array->tail_ptr != NULL) || (
        array->head_ptr != NULL && array->tail_ptr == NULL
    )) {
        return INVALID_ARRAY_ERROR;
    }

    // Check if there is at least one element in the array
    // Further checks aren't needed
    if (array->head_ptr == NULL || array->head_ptr == array->tail_ptr) {
        return NOERROR;
    }

    // More than one element is already in the array
    //
    // Iterating through the whole list is 
    // probably not the most efficient way
    DynamicArrayNode* current_ptr = array->head_ptr;
    while (current_ptr != NULL) {
        if (current_ptr->data == NULL) { 
            return INVALID_ARRAY_ERROR;
        }

        // When the next-pointer after the current is NULL, the current-pointer
        // has to be the tail-pointer.
        if (current_ptr->next_ptr == NULL && current_ptr != array->tail_ptr) {
            return INVALID_ARRAY_ERROR;
        }

        current_ptr = current_ptr->next_ptr;
    }

    return NOERROR;
}

/*
- Append element to dynamic-array.
- Create dynamic-array if `head_ptr` and `tail_ptr` is `NULL` and add element as first and only element.

Returns `ERROR_CODE`:
    - `NOERROR`: Element has been sucessfully appended to the dynamic-array
    - `INVALID_ARRAY_ERROR`: Given dynamic-array is invalid (missing or invalid `head_ptr` and `tail_ptr`)
    - `NULL_PTR_ERROR`: Space allocation error occured
*/
ERROR_CODE append_element(DynamicArray* array, size_t element_size, void* element) {
    ERROR_CODE is_array_invalid = if_invalid_dynamic_array(array);
    if (is_array_invalid != NOERROR) {
        // Given array is invalid.
        return is_array_invalid;
    }

    DynamicArrayNode* current_ptr = (DynamicArrayNode*) calloc(1, sizeof(DynamicArrayNode));
    if (current_ptr == NULL) {
        // Space allocation error
        return NULL_PTR_ERROR;
    }

    current_ptr->data = calloc(1, element_size);
    if (current_ptr->data == NULL) {
        // Space allocation error
        free(current_ptr);
        return NULL_PTR_ERROR;
    }

    // Copy data
    memcpy(current_ptr->data, element, element_size);
    current_ptr->data_size = element_size;

    // current-pointer is the new tail-pointer
    current_ptr->next_ptr = NULL;

    if (array->head_ptr == NULL) {
        // First element in array
        array->head_ptr = current_ptr;
        current_ptr->prev_ptr = NULL;
        
    } else if (array->head_ptr == array->tail_ptr) {
        // Second element in array
        array->head_ptr->next_ptr = current_ptr;
        current_ptr->next_ptr = NULL;
        current_ptr->prev_ptr = array->head_ptr;
    
    } else {
        // At least two elements in array
        array->tail_ptr->next_ptr = current_ptr;
        current_ptr->prev_ptr = array->tail_ptr;
    }

    array->tail_ptr = current_ptr;

    return NOERROR;
}

/*
Free all elements in the given dynamic-array.

Returns `ERROR_CODE`:
    - `NOERROR`: Element has been sucessfully appended to the dynamic-array
    - `INVALID_ARRAY_ERROR`: Given dynamic-array is invalid (missing or invalid `head_ptr` and `tail_ptr`)
*/
ERROR_CODE clear_array(DynamicArray* array) {
    ERROR_CODE is_array_invalid = if_invalid_dynamic_array(array);
    if (is_array_invalid != NOERROR) {
        // Given array is invalid.
        return is_array_invalid;
    }

    DynamicArrayNode* current_ptr = array->head_ptr;

    while (current_ptr->next_ptr != NULL) {
        current_ptr = current_ptr->next_ptr;
        free(current_ptr->prev_ptr->data);
        free(current_ptr->prev_ptr);
    }

    if (current_ptr != array->tail_ptr) {
        return INVALID_ARRAY_ERROR;
    }

    free(current_ptr->data);
    free(current_ptr);

    array->head_ptr = NULL;
    array->tail_ptr = NULL;

    return NOERROR;
}