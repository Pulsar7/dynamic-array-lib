#include "dynamic_array.h"
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

/*
Initialize and clear a new empty dynamic-array.
*/
void test_init_and_clear_new_dyn_array() {
    DynArray dynamic_array;
    assert(init_dyn_array(&dynamic_array) == NO_ERROR);
    assert(clear_dyn_array(&dynamic_array) == NO_ERROR);
}

/*
Append a single integer-value to new dynamic-array.
*/
void test_append_simple_integer_value() {
    DynArray dynamic_array;
    assert(init_dyn_array(&dynamic_array) == NO_ERROR);
    int value = 1337;
    assert(append_element_to_dyn_array(&dynamic_array, (void*)&value, sizeof(int)) == NO_ERROR);
    assert(get_first(&dynamic_array) != NULL);
    assert(*(int*)get_first(&dynamic_array) == value);
    assert(get_first(&dynamic_array) == get_last(&dynamic_array));
    assert(*(int*)get_first(&dynamic_array) == *(int*)get_last(&dynamic_array));
    size_t array_len;
    assert(get_len(&dynamic_array, &array_len) == true);
    assert(array_len == 1);
    assert(clear_dyn_array(&dynamic_array) == NO_ERROR);
    assert(dynamic_array.head_ptr == NULL);
    assert(dynamic_array.tail_ptr == NULL);
}

/*
Append a series of integer-values to new dynamic-array.
*/
void test_append_for_loop_integers() {
    DynArray dynamic_array;
    assert(init_dyn_array(&dynamic_array) == NO_ERROR);
    for (int value = 0; value < 50000; value++) {
        assert(append_element_to_dyn_array(&dynamic_array, (void*)&value, sizeof(int)) == NO_ERROR);
    }
    assert(get_first(&dynamic_array) != get_last(&dynamic_array));
    assert(*(int*)get_first(&dynamic_array) != *(int*)get_last(&dynamic_array));
    size_t array_len;
    assert(get_len(&dynamic_array, &array_len) == true);
    assert(array_len == 50000);
    void* data = get_element_by_index(&dynamic_array, (size_t)25555);
    assert(data != NULL);
    assert(*(int*)data == 25555);
    //
    // Index out of bounds
    data = get_element_by_index(&dynamic_array, (size_t)50000);
    assert(data == NULL);
    //
    // Clear dynamic-array
    assert(clear_dyn_array(&dynamic_array) == NO_ERROR);
    assert(dynamic_array.head_ptr == NULL);
    assert(dynamic_array.tail_ptr == NULL);
}

/*
Append elements of static-array to new dynamic-array.
*/
void test_append_static_array() {
    DynArray dynamic_array;
    assert(init_dyn_array(&dynamic_array) == NO_ERROR);
    //
    // Append static-integer-array to dynamic-array
    int static_int_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    assert(append_static_array_elements_to_dyn_array(&dynamic_array, (void*)static_int_array, sizeof(int), (size_t)9) == NO_ERROR);
    assert(get_first(&dynamic_array) != get_last(&dynamic_array));
    assert(*(int*)get_first(&dynamic_array) != *(int*)get_last(&dynamic_array));
    size_t array_len;
    assert(get_len(&dynamic_array, &array_len) == true);
    assert(array_len == 9);
    //
    // Append string to dynamic-array
    char* static_char_array = "HeLlO WoRlD";
    size_t static_char_array_len = strlen(static_char_array);
    assert(append_static_array_elements_to_dyn_array(&dynamic_array, (void*)static_char_array, sizeof(char), static_char_array_len) == NO_ERROR);
    assert(get_first(&dynamic_array) != get_last(&dynamic_array));
    assert(*(char*)get_first(&dynamic_array) != *(char*)get_last(&dynamic_array));
    assert(get_len(&dynamic_array, &array_len) == true);
    assert(array_len == 9+static_char_array_len);
    //
    // Clear dynamic-array
    assert(clear_dyn_array(&dynamic_array) == NO_ERROR);
    assert(dynamic_array.head_ptr == NULL);
    assert(dynamic_array.tail_ptr == NULL);
}

/*
Append whole static-array as one element to new dynamic-array.
*/
void test_append_static_array_as_one_element() {
    DynArray dynamic_array;
    assert(init_dyn_array(&dynamic_array) == NO_ERROR);
    //
    // Add string as one element to dynamic-array (one node)
    char* static_char_array = "HeLlO WoRlD";
    size_t static_char_array_len = strlen(static_char_array);
    assert(append_element_to_dyn_array(&dynamic_array, (void*)static_char_array, sizeof(char)*((size_t)static_char_array_len)) == NO_ERROR);
    assert(get_first(&dynamic_array) == get_last(&dynamic_array));
    size_t array_len;
    assert(get_len(&dynamic_array, &array_len) == true);
    assert(array_len == 1);
    //
    // Get string from dynamic-array
    assert(strncmp((char*)get_element_by_index(&dynamic_array, 0), static_char_array, static_char_array_len) == 0);
    //
    // Clear dynamic-array
    assert(clear_dyn_array(&dynamic_array) == NO_ERROR);
    assert(dynamic_array.head_ptr == NULL);
    assert(dynamic_array.tail_ptr == NULL);
}

/*
Append elements of dynamic-array to another dynamic-array.
*/
void test_append_dyn_arrays_inplace() {
    DynArray dynamic_array_a, dynamic_array_b;
    assert(init_dyn_array(&dynamic_array_a) == NO_ERROR);
    assert(init_dyn_array(&dynamic_array_b) == NO_ERROR);
    //
    // Add string as one element to dynamic-array-B (one node)
    char* static_char_array = "HeLlO WoRlD";
    size_t static_char_array_len = strlen(static_char_array);
    assert(append_element_to_dyn_array(&dynamic_array_b, (void*)static_char_array, sizeof(char)*((size_t)static_char_array_len)) == NO_ERROR);
    assert(get_first(&dynamic_array_b) == get_last(&dynamic_array_b));
    size_t array_len;
    assert(get_len(&dynamic_array_b, &array_len) == true);
    assert(array_len == 1);
    //
    // Append string-element from dynamic-array-B to dynamic-array-A
    assert(append_dyn_arrays_inplace(&dynamic_array_a, &dynamic_array_b) == true);
    assert(get_len(&dynamic_array_a, &array_len) == true);
    assert(array_len == 1);
    //
    // Append string-element from dynamic-array-B to dynamic-array-A again
    assert(append_dyn_arrays_inplace(&dynamic_array_a, &dynamic_array_b) == true);
    assert(get_len(&dynamic_array_a, &array_len) == true);
    assert(array_len == 2);
    //
    // Get both string-elements from dynamic-array-A
    assert(strncmp((char*)get_element_by_index(&dynamic_array_a, 0), static_char_array, static_char_array_len) == 0);
    assert(strncmp((char*)get_element_by_index(&dynamic_array_a, 1), static_char_array, static_char_array_len) == 0);
    //
    // Clear dynamic-arrays
    assert(clear_dyn_array(&dynamic_array_a) == NO_ERROR);
    assert(dynamic_array_a.head_ptr == NULL);
    assert(dynamic_array_a.tail_ptr == NULL);
    assert(clear_dyn_array(&dynamic_array_b) == NO_ERROR);
    assert(dynamic_array_b.head_ptr == NULL);
    assert(dynamic_array_b.tail_ptr == NULL);
}

int main() {
    test_init_and_clear_new_dyn_array();
    test_append_simple_integer_value();
    test_append_for_loop_integers();
    test_append_static_array();
    test_append_static_array_as_one_element();
    test_append_dyn_arrays_inplace();

    return 0;
}