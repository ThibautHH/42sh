#include <criterion/criterion.h>

#include "ice/array.h"
#include "ice/string.h"

Test(ice_array_len, basic) {
    char *array[] = {"Hello", "World", "!", NULL};
    unsigned long long len = ice_array_len((void **)array);

    cr_assert_eq(len, 3, "ice_array_len() returned %lli instead of 3", len);
}

Test(ice_array_len, null) {
    char *array[] = {NULL};
    unsigned long long len = ice_array_len((void **)array);

    cr_assert_eq(len, 0, "ice_array_len() returned %lli instead of 0", len);
}

Test(ice_free_array, basic) {
    char **array = ice_strsplit("Hello World!", " ");

    ice_free_array((void **)array);
}
