#ifndef DYNAMIC_ARRAY_LIB_DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_LIB_DYNAMIC_ARRAY_H

#include <stddef.h>
#include <stdbool.h>

/*
Define enums, structs
*/
typedef enum Error_Code {
    NO_ERROR=0,
    INVALID_ARRAY_ERROR=1,
    NULL_PTR_ERROR=2,
    INVALID_DATA_SIZE=3,
    INVALID_INDEX_ERROR=4
} Error_Code;

typedef struct DynArrayNode {
    void* data;
    size_t data_size;
    struct DynArrayNode* next_ptr;
    struct DynArrayNode* prev_ptr;
} DynArrayNode;

typedef struct DynArray {
    struct DynArrayNode* head_ptr;
    struct DynArrayNode* tail_ptr;
    size_t length;
} DynArray;

/*
Functions
*/
Error_Code init_dyn_array(DynArray* dynamic_array);
Error_Code append_element_to_dyn_array(DynArray* dynamic_array, void* data, const size_t data_size);
void* get_last(const DynArray* dynamic_array);
void* get_first(const DynArray* dynamic_array);
bool get_len(const DynArray* dynamic_array, size_t* len);
Error_Code append_static_array_elements_to_dyn_array(DynArray* dynamic_array, void* static_array, const size_t static_array_elem_size, const size_t static_array_len);
void* get_element_by_index(const DynArray* dynamic_array, const size_t index);
bool append_dyn_arrays_inplace(DynArray* a, const DynArray* b);
Error_Code clear_dyn_array(DynArray* dynamic_array);

#endif // DYNAMIC_ARRAY_LIB_DYNAMIC_ARRAY_H