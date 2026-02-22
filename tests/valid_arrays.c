#include <assert.h>
#include <stdio.h>
//
#include "constants.h"
#include "dynamic_array.h"

/*
    Test valid arrays with one element
*/
void test_init_array_integer_element() {
    DynamicArray dynamic_array;
    init_array(&dynamic_array);
    int integer = 3;

    assert(append_element(&dynamic_array, sizeof(int), (void*)&integer) == NOERROR);
    assert(dynamic_array.head_ptr != NULL);
    assert(dynamic_array.tail_ptr != NULL);
    assert(dynamic_array.head_ptr == dynamic_array.tail_ptr);
    assert(dynamic_array.head_ptr->data_size == sizeof(int));
    assert(dynamic_array.head_ptr->data != NULL);
    assert(*(int*)dynamic_array.head_ptr->data == 3);

    clear_array(&dynamic_array);
}

void test_clear_array_one_integer_element() {
    DynamicArray dynamic_array;
    init_array(&dynamic_array);
    int integer = 3;

    append_element(&dynamic_array, sizeof(int), (void*)&integer);

    assert(clear_array(&dynamic_array) == NOERROR);
    assert(dynamic_array.head_ptr == NULL);
    assert(dynamic_array.tail_ptr == NULL);
}


/*
    Test valid arrays with two elements
*/
void test_append_two_integer_elements() {
    DynamicArray dynamic_array;
    init_array(&dynamic_array);
    int first_integer = 3;
    int second_integer = 5;

    append_element(&dynamic_array, sizeof(int), (void*)&first_integer);
    assert(append_element(&dynamic_array, sizeof(int), (void*)&second_integer) == NOERROR);
    assert(dynamic_array.head_ptr != dynamic_array.tail_ptr);
    assert(*(int*)dynamic_array.head_ptr->data == 3);
    assert(*(int*)dynamic_array.tail_ptr->data == 5);
    assert(dynamic_array.tail_ptr->prev_ptr == dynamic_array.head_ptr);
    assert(dynamic_array.head_ptr->next_ptr == dynamic_array.tail_ptr);

    clear_array(&dynamic_array);
}

void test_clear_array_two_integer_elements() {
    DynamicArray dynamic_array;
    init_array(&dynamic_array);
    int first_integer = 3;
    int second_integer = 5;

    append_element(&dynamic_array, sizeof(int), (void*)&first_integer);
    append_element(&dynamic_array, sizeof(int), (void*)&second_integer);

    assert(clear_array(&dynamic_array) == NOERROR);
    assert(dynamic_array.head_ptr == NULL);
    assert(dynamic_array.tail_ptr == NULL);
}


/*
    Test valid arrays with multiple elements
*/
void test_append_multiple_integer_elements() {
    DynamicArray dynamic_array;
    init_array(&dynamic_array);
    const int max_integers = 10;

    for (int i=0; i <= max_integers; i++) {
        assert(append_element(&dynamic_array, sizeof(int), (void*)&i) == NOERROR);
    }

    DynamicArrayNode* current_ptr = dynamic_array.head_ptr;
    int i = 0;
    while (current_ptr != NULL) {
        assert(*(int*)current_ptr->data == i++);
        current_ptr = current_ptr->next_ptr;
    }

    assert(dynamic_array.head_ptr != dynamic_array.tail_ptr);

    clear_array(&dynamic_array);
}

void test_clear_array_multiple_integer_elements() {
    DynamicArray dynamic_array;
    init_array(&dynamic_array);
    const int max_integers = 10;
    
    for (int i = 0; i <= max_integers; i++) {
        append_element(&dynamic_array, sizeof(int), (void*)&i);
    }

    assert(clear_array(&dynamic_array) == NOERROR);
    assert(dynamic_array.head_ptr == NULL);
    assert(dynamic_array.tail_ptr == NULL);
}


/*
    Test valid arrays with another dynamic-array as element
*/
void test_append_another_dynamic_array_as_element() {
    DynamicArray dynamic_array;
    init_array(&dynamic_array);

    DynamicArray sub_dynamic_array;
    init_array(&sub_dynamic_array);
    int sub_array_integer = 7;
    append_element(&sub_dynamic_array, sizeof(int), (void*)&sub_array_integer);

    assert(append_element(&dynamic_array, sizeof(DynamicArray), (void*)&sub_dynamic_array) == NOERROR);
    assert(dynamic_array.head_ptr->data_size == sizeof(DynamicArray));
    assert(*(int*)((DynamicArray*)dynamic_array.head_ptr->data)->head_ptr->data == sub_array_integer);
    assert(*(int*)((DynamicArray*)dynamic_array.head_ptr->data)->tail_ptr->data == sub_array_integer);
    assert(*(int*)((DynamicArray*)dynamic_array.tail_ptr->data)->head_ptr->data == sub_array_integer);
    assert(*(int*)((DynamicArray*)dynamic_array.tail_ptr->data)->tail_ptr->data == sub_array_integer);

    clear_array(&sub_dynamic_array);
    clear_array(&dynamic_array);
}

void test_clear_array_another_dynamic_array_as_element() {
    DynamicArray dynamic_array;
    init_array(&dynamic_array);

    DynamicArray sub_dynamic_array;
    init_array(&sub_dynamic_array);
    int sub_array_integer = 7;
    
    append_element(&sub_dynamic_array, sizeof(int), (void*)&sub_array_integer);
    append_element(&dynamic_array, sizeof(DynamicArray), (void*)&sub_dynamic_array);

    assert(clear_array(&dynamic_array) == NOERROR);
    assert(clear_array(&sub_dynamic_array) == NOERROR);
}

/*
    Test valid arrays with multiple other dynamic-array as elements

    - Each sub-dynamic-array has only one element
*/
void test_append_multiple_other_dynamic_arrays_as_elements() {
    DynamicArray dynamic_array;
    init_array(&dynamic_array);

    DynamicArray sub_dynamic_array;
    const int max_sub_dyn_arrays = 10;
    for (int array_counter = 0; array_counter <= max_sub_dyn_arrays; array_counter++) {
        init_array(&sub_dynamic_array);
        assert(append_element(&sub_dynamic_array, sizeof(int), (void*)&array_counter) == NOERROR);
        assert(append_element(&dynamic_array, sizeof(DynamicArray), (void*)&sub_dynamic_array) == NOERROR);
    }

    DynamicArrayNode* current_ptr = dynamic_array.head_ptr;
    int i = 0;
    while (current_ptr != NULL) {
        assert(*(int*)((DynamicArray*)current_ptr->data)->head_ptr->data == i++);
        current_ptr = current_ptr->next_ptr;
    }

    current_ptr = dynamic_array.head_ptr;
    while (current_ptr != NULL) {
        clear_array((DynamicArray*)current_ptr->data);
        current_ptr = current_ptr->next_ptr;
    }

    clear_array(&dynamic_array);
}

void test_clear_array_multiple_other_dynamic_arrays_as_elements() {
    DynamicArray dynamic_array;
    init_array(&dynamic_array);

    DynamicArray sub_dynamic_array;
    const int max_sub_dyn_arrays = 10;
    for (int array_counter = 0; array_counter <= max_sub_dyn_arrays; array_counter++) {
        init_array(&sub_dynamic_array);
        append_element(&sub_dynamic_array, sizeof(int), (void*)&array_counter);
        assert(append_element(&dynamic_array, sizeof(DynamicArray), (void*)&sub_dynamic_array) == NOERROR);
    }

    DynamicArrayNode* current_ptr = dynamic_array.head_ptr;
    while (current_ptr != NULL) {
        assert(clear_array((DynamicArray*)current_ptr->data) == NOERROR);
        current_ptr = current_ptr->next_ptr;
    }

    assert(clear_array(&dynamic_array) == NOERROR);
}


/*
    Test valid two-dimensional dynamic-arrays with one-dimensional dynamic-arrays as elements

    - Each sub-dynamic-array has multiple elements
*/
void test_append_one_dimensional_dyn_arrays_to_two_dimensional_array() {
    DynamicArray one_dimensional_array;
    init_array(&one_dimensional_array);

    DynamicArray two_dimensional_array;
    const int max_two_dim_arrays = 3;
    const int max_two_dim_arrays_elements = 3;
    for (int array_counter = 0; array_counter <= max_two_dim_arrays; array_counter++) {
        init_array(&two_dimensional_array);
        for (int sub_element = 0; sub_element <= max_two_dim_arrays_elements; sub_element++) {
            assert(append_element(&two_dimensional_array, sizeof(int), (void*)&sub_element) == NOERROR);
        }
        assert(append_element(&one_dimensional_array, sizeof(DynamicArray), (void*)&two_dimensional_array) == NOERROR);
    }

    DynamicArrayNode* current_ptr = one_dimensional_array.head_ptr;
    DynamicArrayNode* two_dim_array_current_ptr = NULL;
    int element = 0;
    while (current_ptr != NULL) {
        two_dim_array_current_ptr = ((DynamicArray*)current_ptr->data)->head_ptr;
        element = 0;
        while (two_dim_array_current_ptr != NULL) {
            assert(*(int*)two_dim_array_current_ptr->data == element++);
            two_dim_array_current_ptr = two_dim_array_current_ptr->next_ptr;
        } 
        current_ptr = current_ptr->next_ptr;
    }

    current_ptr = one_dimensional_array.head_ptr;
    while (current_ptr != NULL) {
        clear_array((DynamicArray*)current_ptr->data);
        current_ptr = current_ptr->next_ptr;
    }

    clear_array(&one_dimensional_array);
}

void test_clear_one_dimensional_dyn_arrays_in_two_dimensional_array() {
    DynamicArray one_dimensional_array;
    init_array(&one_dimensional_array);

    DynamicArray two_dimensional_array;
    const int max_two_dim_arrays = 10;
    const int max_two_dim_arrays_elements = 10;
    for (int array_counter = 0; array_counter <= max_two_dim_arrays; array_counter++) {
        init_array(&two_dimensional_array);
        for (int sub_element = 0; sub_element <= max_two_dim_arrays_elements; sub_element++) {
            assert(append_element(&two_dimensional_array, sizeof(int), (void*)&sub_element) == NOERROR);
        }
        assert(append_element(&one_dimensional_array, sizeof(DynamicArray), (void*)&two_dimensional_array) == NOERROR);
    }

    DynamicArrayNode* current_ptr = one_dimensional_array.head_ptr;
    while (current_ptr != NULL) {
        clear_array((DynamicArray*)current_ptr->data);
        current_ptr = current_ptr->next_ptr;
    }

    assert(clear_array(&one_dimensional_array) == NOERROR);
}