#include <stdio.h>
//
#include "tests.h"

int main(int argc, const char** argv) {
    (void)argc;
    (void)argv;

    printf("<--------Running Tests for Custom-DynamicArrayLib-------->\n");
    
    printf("> Testing valid arrays\n");
    printf("  > Testing 'test_init_array_integer_element()'...");
    test_init_array_integer_element();
    printf("O.K.\n");
    printf("  > Testing 'test_clear_array_one_integer_element()'...");
    test_clear_array_one_integer_element();
    printf("O.K.\n");

    printf("  > Testing 'test_append_two_integer_elements()'...");
    test_append_two_integer_elements();
    printf("O.K.\n");
    printf("  > Testing 'test_clear_array_two_integer_elements()'...");
    test_clear_array_two_integer_elements();
    printf("O.K.\n");

    printf("  > Testing 'test_append_multiple_integer_elements()'...");
    test_append_multiple_integer_elements();
    printf("O.K.\n");
    printf("  > Testing 'test_clear_array_multiple_integer_elements()'...");
    test_clear_array_multiple_integer_elements();
    printf("O.K.\n");

    printf("  > Testing 'test_append_another_dynamic_array_as_element()'...");
    test_append_another_dynamic_array_as_element();
    printf("O.K.\n");
    printf("  > Testing 'test_clear_array_another_dynamic_array_as_element()'...");
    test_clear_array_another_dynamic_array_as_element();
    printf("O.K.\n");

    printf("  > Testing 'test_append_multiple_other_dynamic_array_as_elements()'...");
    test_append_multiple_other_dynamic_array_as_elements();
    printf("O.K.\n");
    printf("  > Testing 'test_clear_array_multiple_other_dynamic_array_as_elements()'...");
    test_clear_array_multiple_other_dynamic_array_as_elements();
    printf("O.K.\n");

    printf("  > Testing 'test_append_multiple_other_dynamic_array_as_elements_with_multiple_subelements()'...");
    test_append_multiple_other_dynamic_array_as_elements_with_multiple_subelements();
    printf("O.K.\n");
    printf("  > Testing 'test_clear_array_multiple_other_dynamic_array_as_elements_with_multiple_subelements()'...");
    test_clear_array_multiple_other_dynamic_array_as_elements_with_multiple_subelements();
    printf("O.K.\n");

    printf("\n> Testing invalid arrays\n");
    printf("  > Testing 'test_invalid_head_tail_ptr_array()'...");
    test_invalid_head_tail_ptr_array();
    printf("O.K.\n");

    printf("  > Testing 'test_null_init_array()'...");
    test_null_init_array();
    printf("O.K.\n");
}