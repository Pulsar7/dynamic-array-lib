#ifndef CUSTOM_DYNAMIC_ARRAY_LIB_DYNAMIC_ARRAY_H
#define CUSTOM_DYNAMIC_ARRAY_LIB_DYNAMIC_ARRAY_H

#include <stdlib.h>
//
#include "constants.h"

typedef struct DynamicArrayNode {
    void* data;
    size_t data_size;
    struct DynamicArrayNode* next_ptr;
    struct DynamicArrayNode* prev_ptr;
} DynamicArrayNode;

typedef struct DynamicArray {
    DynamicArrayNode* head_ptr;
    DynamicArrayNode* tail_ptr;
} DynamicArray;

/*
Functions
*/
ERROR_CODE init_array(DynamicArray* array);
ERROR_CODE append_element(DynamicArray* array, size_t element_size, void* element);
ERROR_CODE clear_array(DynamicArray* array);

#endif // CUSTOM_DYNAMIC_ARRAY_LIB_DYNAMIC_ARRAY_H
