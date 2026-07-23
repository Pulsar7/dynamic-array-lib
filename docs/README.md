# DynamicArray-Library <!-- omit in toc -->

## Table of Contents <!-- omit in toc -->

- [Description](#description)
- [Usage](#usage)
  - [Initialize \& Clear Dynamic-Array](#initialize--clear-dynamic-array)
  - [Append elements to Dynamic-Array](#append-elements-to-dynamic-array)
  - [Get length of Dynamic-Array](#get-length-of-dynamic-array)
  - [Append elements of static-array to Dynamic-Array](#append-elements-of-static-array-to-dynamic-array)
  - [Get element of Dynamic-array by index](#get-element-of-dynamic-array-by-index)
  - [Append two Dynamic-Arrays inplace](#append-two-dynamic-arrays-inplace)
  - [Swap position of elements in Dynamic-Array](#swap-position-of-elements-in-dynamic-array)
  - [Replace an element by index](#replace-an-element-by-index)
  - [Insert an element at an index](#insert-an-element-at-an-index)
  - [Sort-Algorithms](#sort-algorithms)
    - [Bubble-Sort](#bubble-sort)
    - [Merge-Sort](#merge-sort)
- [ToDo](#todo)

## Description

> [!IMPORTANT]
> For educational purposes only. Please don't use this library in a real-world implementation.

## Usage

### Initialize & Clear Dynamic-Array

```C
//
// Initialize dynamic-array
DynArray dynamic_array;
if (init_dyn_array(&dynamic_array) != NO_ERROR) {
    return 1;
}
//
// Clear dynamic-array
if (clear_dyn_array(&dynamic_array) != NO_ERROR) {
    return 1;
}

return 0;
```

### Append elements to Dynamic-Array

```C
//
// Initialize dynamic-array
DynArray dynamic_array;
if (init_dyn_array(&dynamic_array) != NO_ERROR) {
    return 1;
}
//
// Append one element to dynamic-array
int value_A = 1337;
if (append_element_to_dyn_array(&dynamic_array, (void*)&value_A, sizeof(int)) != NO_ERROR) {
    printf("Couldn't append new element to dynamic-array\n");
}
//
// Append 50 elements to dynamic-array
for (int value = 0; value < 50; value++) {
    if (append_element_to_dyn_array(&dynamic_array, (void*)&value, sizeof(int)) != NO_ERROR) {
        printf("Couldn't append new element to dynamic-array\n");
        break;
    }
}
//
// Clear dynamic-array
if (clear_dyn_array(&dynamic_array) != NO_ERROR) {
    return 1;
}

return 0;
```

### Get length of Dynamic-Array

```C
//
// Initialize dynamic-array
DynArray dynamic_array;
if (init_dyn_array(&dynamic_array) != NO_ERROR) {
    return 1;
}
//
// Append 50 elements to dynamic-array
for (int value = 0; value < 50; value++) {
    if (append_element_to_dyn_array(&dynamic_array, (void*)&value, sizeof(int)) != NO_ERROR) {
        printf("Couldn't append new element to dynamic-array\n");
        break;
    }
}
//
// Get amount of elments in dynamic-array
size_t array_len;
if (get_len(&dynamic_array, &array_len) == NO_ERROR) {
    printf("length of dynamic-array=%d\n", array_len);
} else {
    printf("Couldn't get length of dynamic-array\n");
}
//
// Clear dynamic-array
if (clear_dyn_array(&dynamic_array) != NO_ERROR) {
    return 1;
}

return 0;
```

### Append elements of static-array to Dynamic-Array

```C
//
// Initialize dynamic-array
DynArray dynamic_array;
if (init_dyn_array(&dynamic_array) != NO_ERROR) {
    return 1;
}
//
// Add static integer-array to dynamic-array
int static_int_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
if (append_static_array_elements_to_dyn_array(&dynamic_array, static_int_array, sizeof(int), (size_t)9) != NO_ERROR) {
    printf("Couldn't append int-elements of static-array to dynamic-array\n");
}
//
// Add static char-array to dynamic-array
char* static_char_array = "HeLlO WoRlD";
size_t static_char_array_len = strlen(static_char_array);
if (append_static_array_elements_to_dyn_array(&dynamic_array, static_char_array, sizeof(char), static_char_array_len) != NO_ERROR) {
    printf("Couldn't append static-string to dynamic-array\n");
}
//
// Clear dynamic-array
if (clear_dyn_array(&dynamic_array) != NO_ERROR) {
    return 1;
}

return 0;
```

### Get element of Dynamic-array by index

```C
//
// Initialize dynamic-array
DynArray dynamic_array;
if (init_dyn_array(&dynamic_array) != NO_ERROR) {
    return 1;
}
//
// Append string-element to dynamic-array
char* static_char_array = "HeLlO WoRlD";
size_t static_char_array_len = strlen(static_char_array);
size_t data_size = sizeof(char)*((size_t)static_char_array_len);
if (append_element_to_dyn_array(&dynamic_array, (void*)static_char_array, data_size) == NO_ERROR) {
    //
    // Get string-element from dynamic-array by its index
    printf("%s\n", (char*)get_element_by_index(&dynamic_array, 0));
} else {
    printf("Couldn't append static-string to dynamic-array\n");
}
//
// Clear dynamic-array
if (clear_dyn_array(&dynamic_array) != NO_ERROR) {
    return 1;
}

return 0;
```

### Append two Dynamic-Arrays inplace

```C
//
// Initialize both dynamic-arrays
DynArray dynamic_array_a, dynamic_array_b;
if (init_dyn_array(&dynamic_array_a) == NO_ERROR || init_dyn_array(&dynamic_array_b) == NO_ERROR) {
    //
    // Failed to initialize one or both dynamic-arrays
    return 1;
}
//
// Add string as one element to dynamic-array-B (one node)
char* static_char_array = "HeLlO WoRlD";
size_t static_char_array_len = strlen(static_char_array);
if (append_element_to_dyn_array(&dynamic_array_b, (void*)static_char_array, sizeof(char)*((size_t)static_char_array_len)) == NO_ERROR) {
    //
    // Append string-element from dynamic-array-B to dynamic-array-A
    if (append_dyn_arrays_inplace(&dynamic_array_a, &dynamic_array_b) == NO_ERROR) {
        printf("%s\n", (char*)get_element_by_index(&dynamic_array_a, 0));
    }
}
//
// Clear dynamic-arrays
if (clear_dyn_array(&dynamic_array_a) != NO_ERROR || clear_dyn_array(&dynamic_array_b) != NO_ERROR) {
    return 1;
}

return 0;
```

### Swap position of elements in Dynamic-Array

```C 
//
// Initialize dynamic-array
DynArray dynamic_array_a, dynamic_array_b;
if (init_dyn_array(&dynamic_array_a) == NO_ERROR) {
    //
    // Failed to initialize dynamic-array
    return 1;
}
//
// Append static-integer-array to dynamic-array
int static_int_array[] = {5, 19, 9, 1, 2, 8, 3, 7, 6, 10, 11, 13, 14, 12, 16, 17, 15, 18, 20, 4};
size_t static_array_len = sizeof(static_int_array)/sizeof(int);
if (append_static_array_elements_to_dyn_array(&dynamic_array, (void*)static_int_array, sizeof(int), static_array_len) == NO_ERROR) {
    if (swap_elements_by_indices(&dynamic_array, 1, 0) == NO_ERROR) {
        for (int i = 0; (size_t)i < dynamic_array.length; i++) {
            printf("%d; ", *(int*)get_element_by_index(&dynamic_array, i));
        }
        printf("\n");
    }   
}
//
// Clear dynamic-array
if (clear_dyn_array(&dynamic_array_a) != NO_ERROR) {
    return 1;
}

return 0;
```

### Replace an element by index

```C
//
// Initialize dynamic-array
DynArray dyn_a;
if (init_dyn_array(&dyn_a) != NO_ERROR) {
    return 1;
}
//
// Append static-integer-array to dynamic-array
int int_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
if (append_static_array_elements_to_dyn_array(&dyn_a, (void*)int_array, sizeof(int), (size_t)9) == NO_ERROR) {
    //
    // Replace int-element at index 0 with int-element 1337
    int new_data = 1337;
    replace_element_by_index(&dyn_a, (size_t)0, (void*)&new_data, sizeof(int));
}
//
// Clear dynamic-array
if (clear_dyn_array(&dyn_a) != NO_ERROR) {
    return 1;
}

return 0;
```

### Insert an element at an index

```C
//
// Initialize dynamic-array
DynArray dyn_a;
if (init_dyn_array(&dyn_a) != NO_ERROR) {
    return 1;
}
//
// Append static-integer-array to dynamic-array
int int_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
if (append_static_array_elements_to_dyn_array(&dyn_a, (void*)int_array, sizeof(int), (size_t)9) == NO_ERROR) {
    //
    // Insert additional element at index 0
    int new_element = 1337;
    insert_element_at_index(&dyn_a, (size_t)0, (void*)&new_element, sizeof(int));
}
//
// Clear dynamic-array
if (clear_dyn_array(&dyn_a) != NO_ERROR) {
    return 1;
}

return 0;
```


### Sort-Algorithms

> [!IMPORTANT]
> The current sort-algorithm implementations require a `DynArray` with **only** `int`-elements. The one and only "validity-check" iterates the whole `DynArray` with that statement: `current_ptr->data_size != sizeof(int)` - which is not ideal.
> Please make sure that you only use the current implementation with `int`-Dynamic-Arrays.

#### Bubble-Sort

```C
//
// Initialize dynamic-array
DynArray dyn_a;
if (init_dyn_array(&dyn_a) != NO_ERROR) {
    return 1;
}
//
// Append static-integer-array to dynamic-array
int int_array[] = {5, 19, 9, 1, 2, 8, 3, 7, 6, 10, 11, 13, 14, 12, 16, 17, 15, 18, 20, 4};
size_t int_arr_l = sizeof(int_array)/sizeof(int);
if (append_static_array_elements_to_dyn_array(&dyn_a, (void*)int_array, sizeof(int), int_arr_l) == NO_ERROR) {
    //
    // Bubble-Sort array
    SortResult sort_result = sort_dyn_array_integers_inplace(&dyn_a, SORT_ALG_BUBBLE);
}
//
// Clear dynamic-array
if (clear_dyn_array(&dyn_a) != NO_ERROR) {
    return 1;
}

return 0;
```

#### Merge-Sort

```C
//
// Initialize dynamic-array
DynArray dyn_a;
if (init_dyn_array(&dyn_a) != NO_ERROR) {
    return 1;
}
//
// Append static-integer-array to dynamic-array
int int_array[] = {5, 19, 9, 1, 2, 8, 3, 7, 6, 10, 11, 13, 14, 12, 16, 17, 15, 18, 20, 4};
size_t int_arr_l = sizeof(int_array)/sizeof(int);
if (append_static_array_elements_to_dyn_array(&dyn_a, (void*)int_array, sizeof(int), int_arr_l) == NO_ERROR) {
    //
    // Merge-Sort array
    SortResult sort_result = sort_dyn_array_integers_inplace(&dyn_a, SORT_ALG_MERGE);
}
//
// Clear dynamic-array
if (clear_dyn_array(&dyn_a) != NO_ERROR) {
    return 1;
}

return 0;
```

## ToDo

- [ ] Instead of iterating through whole dynamic-array at `get_len`, use `size_t length`-Value of `DynArray`-struct