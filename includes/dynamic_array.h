#ifndef DYNAMIC_ARRAY_LIB_DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_LIB_DYNAMIC_ARRAY_H

#include <stddef.h>

/*
Define enums, structs
*/
typedef enum Error_Code {
    NO_ERROR=0,
    INVALID_ARRAY_ERROR=1,
    NULL_PTR_ERROR=2,
    INVALID_DATA_SIZE=3,
    INVALID_INDEX_ERROR=4,
    INVALID_ARGUMENT_ERROR=5
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
Error_Code check_dyn_array(const DynArray* dynamic_array);
Error_Code init_dyn_array(DynArray* dynamic_array);
Error_Code append_element_to_dyn_array(DynArray* dynamic_array, const void* data, const size_t data_size);
void* get_last(const DynArray* dynamic_array);
void* get_first(const DynArray* dynamic_array);
Error_Code get_len(const DynArray* dynamic_array, size_t* len);
Error_Code append_static_array_elements_to_dyn_array(DynArray* dynamic_array, const void* static_array, const size_t static_array_elem_size, const size_t static_array_len);
DynArrayNode* get_element_ptr_by_index(const DynArray* dynamic_array, const size_t index);
void* get_element_by_index(const DynArray* dynamic_array, const size_t index);
Error_Code append_dyn_arrays_inplace(DynArray* a, const DynArray* b);
Error_Code swap_elements_by_indices(DynArray* dynamic_array, const size_t index_a, const size_t index_b);
Error_Code replace_element_by_index(DynArray* dynamic_array, const size_t index, const void* data, const size_t data_size);
Error_Code insert_element_at_index(DynArray* dynamic_array, const size_t index, const void* data, const size_t data_size);
Error_Code clear_dyn_array(DynArray* dynamic_array);

#endif // DYNAMIC_ARRAY_LIB_DYNAMIC_ARRAY_H