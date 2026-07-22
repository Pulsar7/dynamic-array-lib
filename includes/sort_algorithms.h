#ifndef DYNAMIC_ARRAY_LIB_SORT_ALGORITHMS_H
#define DYNAMIC_ARRAY_LIB_SORT_ALGORITHMS_H

#include "dynamic_array.h"

/*
Define enums, structs
*/
typedef enum Sort_Algorithm {
    SORT_ALG_BUBBLE=0,
    SORT_ALG_MERGE=1
} Sort_Algorithm;

typedef struct SortResult {
    Error_Code error_code;
} SortResult;

/*
Functions
*/

SortResult sort_dyn_array_integers_inplace(DynArray* dynamic_array, Sort_Algorithm sort_algorithm);

#endif // DYNAMIC_ARRAY_LIB_SORT_ALGORITHMS_H