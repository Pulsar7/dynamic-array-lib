#include "dynamic_array.h"
#include <stdio.h>
#include <assert.h>

/*
Append a single integer-value to new created dynamic-array.
*/
void append_simple_integer_value() {
    DynArray dynamic_array;
    assert(init_dyn_array(&dynamic_array) == NO_ERROR);
    int value = 1337;
    assert(append_element_to_dyn_array(&dynamic_array, (void*)&value, sizeof(int)) == NO_ERROR);
    assert(get_first(&dynamic_array) != NULL);
    assert(*(int*)get_first(&dynamic_array) == value);
    assert(get_first(&dynamic_array) == get_last(&dynamic_array));
    assert(*(int*)get_first(&dynamic_array) == *(int*)get_last(&dynamic_array));
    assert(clear_dyn_array(&dynamic_array) == NO_ERROR);
    assert(dynamic_array.head_ptr == NULL);
    assert(dynamic_array.tail_ptr == NULL);
}

/*
Append a series of integer-values to new created dynamic-array.
*/
void append_for_loop_integers() {
    DynArray dynamic_array;
    assert(init_dyn_array(&dynamic_array) == NO_ERROR);
    for (int value = 0; value < 50; value++) {
        assert(append_element_to_dyn_array(&dynamic_array, (void*)&value, sizeof(int)) == NO_ERROR);
    }
    assert(get_first(&dynamic_array) != get_last(&dynamic_array));
    assert(*(int*)get_first(&dynamic_array) != *(int*)get_last(&dynamic_array));
    assert(clear_dyn_array(&dynamic_array) == NO_ERROR);
    assert(dynamic_array.head_ptr == NULL);
    assert(dynamic_array.tail_ptr == NULL);
}

int main() {
    //
    append_simple_integer_value();
    append_for_loop_integers();

    return 0;
}