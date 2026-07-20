#ifndef DYNAMIC_ARRAY_LIB_DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_LIB_DYNAMIC_ARRAY_H

/*
Define enums, structs
*/
typedef enum Error_Code {
    NO_ERROR=0,
    INVALID_ARRAY_ERROR=1,
    NULL_PTR_ERROR=2,
    INVALID_DATA_SIZE=3

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
} DynArray;

/*
Functions
*/
//
// Initialize new dynamic array
Error_Code init_dyn_array(DynArray* dynamic_array);
Error_Code append_element_to_dyn_array(DynArray* dynamic_array, void* data, size_t data_size);
Error_Code clear_dyn_array(DynArray* dynamic_array);

#endif // DYNAMIC_ARRAY_LIB_DYNAMIC_ARRAY_H