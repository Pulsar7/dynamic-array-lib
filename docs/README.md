# DynamicArray-Library <!-- omit in toc -->

## Table of Contents <!-- omit in toc -->

- [Usage](#usage)
  - [Create new Dynamic-Array](#create-new-dynamic-array)
  - [Clear Dynamic-Array](#clear-dynamic-array)
  - [Append elements to Dynamic-Array](#append-elements-to-dynamic-array)
  - [Get length of Dynamic-Array](#get-length-of-dynamic-array)

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