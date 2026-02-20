#include <assert.h>
//
#include "constants.h"
#include "dynamic_array.h"

/*
    Test invalid arrays
*/
void test_invalid_head_tail_ptr_array() {
    DynamicArray dynamic_array;
    init_array(&dynamic_array);
    int integer = 3;
    dynamic_array.head_ptr = (DynamicArrayNode*)&integer;
    assert(append_element(&dynamic_array, sizeof(int), (void*)&integer) == INVALID_ARRAY_ERROR);
    dynamic_array.head_ptr = NULL;
    dynamic_array.tail_ptr = (DynamicArrayNode*)&integer;
    assert(append_element(&dynamic_array, sizeof(int), (void*)&integer) == INVALID_ARRAY_ERROR);
    clear_array(&dynamic_array);
}

void test_null_init_array() {
    assert(init_array(NULL) == NULL_PTR_ERROR);
}