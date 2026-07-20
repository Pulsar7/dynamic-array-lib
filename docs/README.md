# DynamicArray-Library <!-- omit in toc -->

## Table of Contents <!-- omit in toc -->

- [Description](#description)
- [Usage](#usage)
  - [Initialize \& Clear Dynamic-Array](#initialize--clear-dynamic-array)
  - [Append elements to Dynamic-Array](#append-elements-to-dynamic-array)
  - [Get length of Dynamic-Array](#get-length-of-dynamic-array)
  - [Append elements of static-array to Dynamic-Array](#append-elements-of-static-array-to-dynamic-array)
  - [Get element of Dynamic-array by index](#get-element-of-dynamic-array-by-index)
  - [Append two Dynamica-Arrays inplace](#append-two-dynamica-arrays-inplace)
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
if (get_len(&dynamic_array, &array_len) == true) {
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

### Append two Dynamica-Arrays inplace

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
    if (append_dyn_arrays_inplace(&dynamic_array_a, &dynamic_array_b)) {
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

## ToDo

- [ ] Instead of iterating through whole dynamic-array at `get_len`, use `size_t length`-Value of `DynArray`-struct