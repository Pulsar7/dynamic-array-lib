#ifndef CUSTOM_DYNAMIC_ARRAY_LIB_TESTS_H
#define CUSTOM_DYNAMIC_ARRAY_LIB_TESTS_H

/*
    Valid arrays
*/
void test_init_array_integer_element();
void test_clear_array_one_integer_element();

void test_append_two_integer_elements();
void test_clear_array_two_integer_elements();

void test_append_multiple_integer_elements();
void test_clear_array_multiple_integer_elements();

void test_append_another_dynamic_array_as_element();
void test_clear_array_another_dynamic_array_as_element();

void test_append_multiple_other_dynamic_arrays_as_elements();
void test_clear_array_multiple_other_dynamic_arrays_as_elements();

void test_append_one_dimensional_dyn_arrays_to_two_dimensional_array();
void test_clear_one_dimensional_dyn_arrays_in_two_dimensional_array();

/*
    Invalid arrays
*/
void test_invalid_head_tail_ptr_array();
void test_null_init_array();

#endif // CUSTOM_DYNAMIC_ARRAY_LIB_TESTS_H