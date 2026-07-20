# DynamicArray-Library <!-- omit in toc -->

## Table of Contents <!-- omit in toc -->

- [Description](#description)
- [Usage](#usage)
  - [Create new Dynamic-Array](#create-new-dynamic-array)
  - [Clear Dynamic-Array](#clear-dynamic-array)
  - [Append elements to Dynamic-Array](#append-elements-to-dynamic-array)
  - [Get length of Dynamic-Array](#get-length-of-dynamic-array)
  - [Append elements of static-array to Dynamic-Array](#append-elements-of-static-array-to-dynamic-array)

## Description

> [!IMPORTANT]
> For educational purposes only. Please don't use this library in a real-world implementation.



## Usage

### Create new Dynamic-Array

```C
DynArray dynamic_array;
if (init_dyn_array(&dynamic_array) != NO_ERROR) {
    return 1;
}
return 0;
```

### Clear Dynamic-Array

```C
DynArray dynamic_array;
if (init_dyn_array(&dynamic_array) != NO_ERROR) {
    return 1;
}

if (clear_dyn_array(&dynamic_array) != NO_ERROR) {
    return 1;
}

return 0;
```

### Append elements to Dynamic-Array

```C
DynArray dynamic_array;
if (init_dyn_array(&dynamic_array) != NO_ERROR) {
    return 1;
}

int value_A = 1337;
if (append_element_to_dyn_array(&dynamic_array, (void*)&value_A, sizeof(int)) != NO_ERROR) {
    printf("Couldn't append new element to dynamic-array\n");
}

for (int value = 0; value < 50; value++) {
    if (append_element_to_dyn_array(&dynamic_array, (void*)&value, sizeof(int)) != NO_ERROR) {
        printf("Couldn't append new element to dynamic-array\n");
        break;
    }
}

if (clear_dyn_array(&dynamic_array) != NO_ERROR) {
    return 1;
}

return 0;
```

### Get length of Dynamic-Array

```C
DynArray dynamic_array;
if (init_dyn_array(&dynamic_array) != NO_ERROR) {
    return 1;
}

for (int value = 0; value < 50; value++) {
    if (append_element_to_dyn_array(&dynamic_array, (void*)&value, sizeof(int)) != NO_ERROR) {
        printf("Couldn't append new element to dynamic-array\n");
        break;
    }
}

size_t array_len;
if (get_len(&dynamic_array, &array_len) == true) {
    printf("length of dynamic-array=%d\n", array_len);
} else {
    printf("Couldn't get length of dynamic-array\n");
}

if (clear_dyn_array(&dynamic_array) != NO_ERROR) {
    return 1;
}

return 0;
```

### Append elements of static-array to Dynamic-Array

```C
DynArray dynamic_array;
if (init_dyn_array(&dynamic_array) != NO_ERROR) {
    return 1;
}

int static_int_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
if (append_static_array_elements_to_dyn_array(&dynamic_array, static_int_array, sizeof(int), (size_t)9) != NO_ERROR) {
    printf("Couldn't append int-elements of static-array to dynamic-array\n");
}

char* static_char_array = "HeLlO WoRlD";
size_t static_char_array_len = strlen(static_char_array);
if (append_static_array_elements_to_dyn_array(&dynamic_array, static_char_array, sizeof(char), static_char_array_len) != NO_ERROR) {
    printf("Couldn't append static-string to dynamic-array\n");
}

if (clear_dyn_array(&dynamic_array) != NO_ERROR) {
    return 1;
}

return 0;
```