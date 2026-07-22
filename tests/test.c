#include "dynamic_array.h"
#include "sort_algorithms.h"
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

/*
Test to swap elements of dynamic-array by its indices.
*/
void test_swap_elements_by_indices() {
    DynArray dynamic_array;
    assert(init_dyn_array(&dynamic_array) == NO_ERROR);
    //
    // Append static-integer-array to dynamic-array
    int static_int_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    assert(append_static_array_elements_to_dyn_array(&dynamic_array, (void*)static_int_array, sizeof(int), (size_t)9) == NO_ERROR);
    /**
     * 
     * Scenario 1: head_ptr and tail_ptr
     * 
     */
    //
    // Get element-a
    size_t element_a_index = 0;
    assert(*(int*)get_element_by_index(&dynamic_array, element_a_index) == 1);
    //
    // Get element-b
    size_t element_b_index = 8;
    assert(*(int*)get_element_by_index(&dynamic_array, element_b_index) == 9);
    //
    // Swap element-a and element-b
    assert(swap_elements_by_indices(&dynamic_array, element_a_index, element_b_index) == NO_ERROR);
    //
    // Get element-a
    assert(*(int*)get_element_by_index(&dynamic_array, element_a_index) == 9);
    //
    // Get element-b
    assert(*(int*)get_element_by_index(&dynamic_array, element_b_index) == 1);
    /**
     * 
     * Scenario 2: neither head_ptr nor tail_ptr
     * 
     */
    //
    // Get element-a
    element_a_index = 1;
    assert(*(int*)get_element_by_index(&dynamic_array, element_a_index) == 2);
    //
    // Get element-b
    element_b_index = 4;
    assert(*(int*)get_element_by_index(&dynamic_array, element_b_index) == 5);
    //
    // Swap element-a and element-b
    assert(swap_elements_by_indices(&dynamic_array, element_a_index, element_b_index) == NO_ERROR);
    //
    // Get element-a
    assert(*(int*)get_element_by_index(&dynamic_array, element_a_index) == 5);
    //
    // Get element-b
    assert(*(int*)get_element_by_index(&dynamic_array, element_b_index) == 2);
    /**
     * 
     * Scenario 3: only head_ptr
     * 
     */
    //
    // Get element-a
    element_a_index = 0;
    assert(*(int*)get_element_by_index(&dynamic_array, element_a_index) == 9);
    //
    // Get element-b
    element_b_index = 4;
    assert(*(int*)get_element_by_index(&dynamic_array, element_b_index) == 2);
    //
    // Swap element-a and element-b
    assert(swap_elements_by_indices(&dynamic_array, element_a_index, element_b_index) == NO_ERROR);
    //
    // Get element-a
    assert(*(int*)get_element_by_index(&dynamic_array, element_a_index) == 2);
    //
    // Get element-b
    assert(*(int*)get_element_by_index(&dynamic_array, element_b_index) == 9);
    /**
     * 
     * Scenario 4: only tail_ptr
     * 
     */
    //
    // Get element-a
    element_a_index = 3;
    assert(*(int*)get_element_by_index(&dynamic_array, element_a_index) == 4);
    //
    // Get element-b
    element_b_index = 8;
    assert(*(int*)get_element_by_index(&dynamic_array, element_b_index) == 1);
    //
    // Swap element-a and element-b
    assert(swap_elements_by_indices(&dynamic_array, element_a_index, element_b_index) == NO_ERROR);
    //
    // Get element-a
    assert(*(int*)get_element_by_index(&dynamic_array, element_a_index) == 1);
    //
    // Get element-b
    assert(*(int*)get_element_by_index(&dynamic_array, element_b_index) == 4);
    //
    // Clear dynamic-array
    assert(clear_dyn_array(&dynamic_array) == NO_ERROR);
    assert(dynamic_array.head_ptr == NULL);
    assert(dynamic_array.tail_ptr == NULL);
    //
    // Re-initialize dynamic-array
    // Which is not required since after calling `clear_dyn_array` re-initializes 
    // the dynamic-array automatically.
    //assert(init_dyn_array(&dynamic_array) == NO_ERROR);
    //
    // Append static-integer-array to dynamic-array
    assert(append_static_array_elements_to_dyn_array(&dynamic_array, (void*)static_int_array, sizeof(int), (size_t)9) == NO_ERROR);
    //
    // Randomly Swap to trigger edge-cases
    assert(*(int*)get_element_by_index(&dynamic_array, 0) == 1);
    assert(*(int*)get_element_by_index(&dynamic_array, 1) == 2);
    assert(swap_elements_by_indices(&dynamic_array, 0, 1) == NO_ERROR);
    assert(swap_elements_by_indices(&dynamic_array, 1, 0) == NO_ERROR);
    assert(*(int*)get_element_by_index(&dynamic_array, 0) == 1);
    assert(*(int*)get_element_by_index(&dynamic_array, 1) == 2);

    assert(swap_elements_by_indices(&dynamic_array, 4, 7) == NO_ERROR);
    assert(*(int*)get_element_by_index(&dynamic_array, 4) == 8);
    assert(*(int*)get_element_by_index(&dynamic_array, 7) == 5);

    assert(swap_elements_by_indices(&dynamic_array, 7, 4) == NO_ERROR);
    assert(*(int*)get_element_by_index(&dynamic_array, 4) == 5);
    assert(*(int*)get_element_by_index(&dynamic_array, 7) == 8);

    assert(swap_elements_by_indices(&dynamic_array, 0, 8) == NO_ERROR);
    assert(*(int*)get_element_by_index(&dynamic_array, 0) == 9);
    assert(*(int*)get_element_by_index(&dynamic_array, 8) == 1);

    assert(swap_elements_by_indices(&dynamic_array, 8, 0) == NO_ERROR);
    assert(*(int*)get_element_by_index(&dynamic_array, 0) == 1);
    assert(*(int*)get_element_by_index(&dynamic_array, 8) == 9);

    assert(swap_elements_by_indices(&dynamic_array, 0, 8) == NO_ERROR);
    assert(*(int*)get_element_by_index(&dynamic_array, 0) == 9);
    assert(*(int*)get_element_by_index(&dynamic_array, 8) == 1);
    //
    // Clear dynamic-array
    assert(clear_dyn_array(&dynamic_array) == NO_ERROR);
}

void test_replace_element_by_index() {
    DynArray dynamic_array;
    assert(init_dyn_array(&dynamic_array) == NO_ERROR);
    //
    // Append static-integer-array to dynamic-array
    int static_int_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    assert(append_static_array_elements_to_dyn_array(&dynamic_array, (void*)static_int_array, sizeof(int), (size_t)9) == NO_ERROR);
    int new_data = 1337;
    assert(replace_element_by_index(&dynamic_array, (size_t)0, (void*)&new_data, sizeof(int)) == NO_ERROR);
    assert(*(int*)get_element_by_index(&dynamic_array, 0) == 1337);
    //
    // Replace element at index 1 with string
    char* new_string_data = "hello world. this is not a test ";
    size_t new_string_len = strlen(new_string_data);
    assert(replace_element_by_index(&dynamic_array, (size_t)1, (void*)new_string_data, new_string_len) == NO_ERROR);
    assert(strncmp((char*)get_element_by_index(&dynamic_array, (size_t)1), new_string_data, new_string_len) == 0);
    //
    // Clear dynamic-array
    assert(clear_dyn_array(&dynamic_array) == NO_ERROR);
    assert(dynamic_array.head_ptr == NULL);
    assert(dynamic_array.tail_ptr == NULL);
}

//

/*
Test sort-algorithms-function for integers bubble-sort inplace.
*/
void test_integers_bubble_sort_inplace() {
    DynArray dynamic_array;
    assert(init_dyn_array(&dynamic_array) == NO_ERROR);
    //
    // Append static-integer-array to dynamic-array
    int static_int_array[] = {5, 19, 9, 1, 2, 8, 3, 7, 6, 10, 11, 13, 14, 12, 16, 17, 15, 18, 20, 4};
    assert(append_static_array_elements_to_dyn_array(&dynamic_array, (void*)static_int_array, sizeof(int), sizeof(static_int_array)/sizeof(int)) == NO_ERROR);
    assert(swap_elements_by_indices(&dynamic_array, 1, 0) == NO_ERROR);
    assert(*(int*)get_element_by_index(&dynamic_array, 0) == 19);
    assert(*(int*)get_element_by_index(&dynamic_array, 1) == 5);
    assert(*(int*)get_element_by_index(&dynamic_array, 2) == 9);
    assert(*(int*)get_element_by_index(&dynamic_array, 17) == 18);
    //
    // Bubble-Sort array
    SortResult sort_result = sort_dyn_array_integers_inplace(&dynamic_array, SORT_ALG_BUBBLE);
    assert(sort_result.error_code == NO_ERROR);
    for (int i = 0; (size_t)i < dynamic_array.length; i++) {
        assert(*(int*)get_element_by_index(&dynamic_array, i) == i+1);
    }
    //
    // Clear dynamic-array
    assert(clear_dyn_array(&dynamic_array) == NO_ERROR);
    assert(dynamic_array.head_ptr == NULL);
    assert(dynamic_array.tail_ptr == NULL);
}

void test_integer_merge_sort_inplace() {
    DynArray dynamic_array;
    assert(init_dyn_array(&dynamic_array) == NO_ERROR);
    //
    // Append static-integer-array to dynamic-array
    int static_int_array[] = {38, 27, 43, 3, 9, 82, 10};
    size_t static_int_array_len = sizeof(static_int_array)/sizeof(int);
    assert(append_static_array_elements_to_dyn_array(&dynamic_array, (void*)static_int_array, sizeof(int), static_int_array_len) == NO_ERROR);
    assert(dynamic_array.length == static_int_array_len);
    //
    // Merge-Sort array
    SortResult sort_result = sort_dyn_array_integers_inplace(&dynamic_array, SORT_ALG_MERGE);
    assert(sort_result.error_code == NO_ERROR);
    assert(*(int*)get_element_by_index(&dynamic_array, 0) == 3);
    assert(*(int*)get_element_by_index(&dynamic_array, 1) == 9);
    assert(*(int*)get_element_by_index(&dynamic_array, 2) == 10);
    assert(*(int*)get_element_by_index(&dynamic_array, 3) == 27);
    assert(*(int*)get_element_by_index(&dynamic_array, 4) == 38);
    assert(*(int*)get_element_by_index(&dynamic_array, 5) == 43);
    assert(*(int*)get_element_by_index(&dynamic_array, 6) == 82);
    //
    // Clear dynamic-array
    assert(clear_dyn_array(&dynamic_array) == NO_ERROR);
    assert(dynamic_array.head_ptr == NULL);
    assert(dynamic_array.tail_ptr == NULL);
}

int main() {
    test_init_and_clear_new_dyn_array();
    test_append_simple_integer_value();
    test_append_for_loop_integers();
    test_append_static_array();
    test_append_static_array_as_one_element();
    test_append_dyn_arrays_inplace();
    test_swap_elements_by_indices();
    test_replace_element_by_index();

    //

    test_integers_bubble_sort_inplace();
    test_integer_merge_sort_inplace();

    return 0;
}