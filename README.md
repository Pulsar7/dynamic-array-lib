<h1>DynamicArrayLib for C</h1>

> [!IMPORTANT]
> For educational purposes only. Please don't use this library in a real-world implementation.

## Table of contents

- [Table of contents](#table-of-contents)
- [Examples](#examples)
  - [Create dynamic array of integers](#create-dynamic-array-of-integers)
  - [Create two dimensional dynamic array of integers](#create-two-dimensional-dynamic-array-of-integers)

## Examples

### Create dynamic array of integers

```C
DynamicArray dynamic_array;
init_array(&dynamic_array);

const int max_integers = 10;

for (int i=0; i <= max_integers; i++) {
    append_element(&dynamic_array, sizeof(int), (void*)&i);
}

// Don't forget to deallocate
clear_array(&dynamic_array);
```

### Create two dimensional dynamic array of integers

```C
DynamicArray dynamic_array;
init_array(&dynamic_array);

DynamicArray sub_dynamic_array;
const int max_sub_dyn_arrays = 10;

for (int array_counter = 0; array_counter <= max_sub_dyn_arrays; array_counter++) {
    init_array(&sub_dynamic_array);
    append_element(&sub_dynamic_array, sizeof(int), (void*)&array_counter);
    append_element(&dynamic_array, sizeof(DynamicArray), (void*)&sub_dynamic_array);
}

// Don't forget to deallocate
DynamicArrayNode* current_ptr = dynamic_array.head_ptr;
int i = 0;
while (current_ptr != NULL) {
    clear_array((DynamicArray*)current_ptr->data);
    current_ptr = current_ptr->next_ptr;
}
clear_array(&dynamic_array);
```