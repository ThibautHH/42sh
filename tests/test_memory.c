#include <criterion/criterion.h>

#include "ice/memory.h"

Test(ice_calloc, basic)
{
    char *str = ice_calloc(10, sizeof(char));

    cr_assert_not_null(str);
    for (int i = 0 ; i < 10 ; i++)
        cr_assert_eq(str[i], 0);
    free(str);
}

Test(ice_memset, basic)
{
    char *str = ice_calloc(10, sizeof(char));

    cr_assert_not_null(str);
    ice_memset(str, 'a', 10);
    for (int i = 0 ; i < 10 ; i++)
        cr_assert_eq(str[i], 'a');
    free(str);
}

Test(ice_memchr, basic)
{
    char *str = ice_calloc(10, sizeof(char));

    cr_assert_not_null(str);
    ice_memset(str, 'a', 10);
    cr_assert_eq(ice_memchr(str, 'a', 10), str);
    cr_assert_eq(ice_memchr(str, 'a', 5), str);
    cr_assert_eq(ice_memchr(str, 'a', 1), str);
    cr_assert_null(ice_memchr(str, 'a', 0));
    free(str);
}

Test(ice_memcmp, basic)
{
    char *str1 = ice_calloc(10, sizeof(char));
    char *str2 = ice_calloc(10, sizeof(char));

    cr_assert_not_null(str1);
    cr_assert_not_null(str2);
    cr_assert_eq(ice_memcmp(str1, str2, 10), 0);
    ice_memset(str1, 'a', 10);
    cr_assert_eq(ice_memcmp(str1, str2, 10), 'a');
    ice_memset(str2, 'b', 10);
    cr_assert_eq(ice_memcmp(str1, str2, 10), 'a' - 'b');
    ice_memset(str2, 'a', 10);
    cr_assert_eq(ice_memcmp(str1, str2, 10), 0);
    ice_memset(str2, 'a', 5);
    cr_assert_eq(ice_memcmp(str1, str2, 10), 0);
    ice_memset(str2, 'a', 1);
    cr_assert_eq(ice_memcmp(str1, str2, 10), 0);
    cr_assert_eq(ice_memcmp(str1, str2, 0), 0);
    free(str1);
    free(str2);
}

Test(ice_memcpy, basic)
{
    char *str1 = ice_calloc(10, sizeof(char));
    char *str2 = ice_calloc(10, sizeof(char));

    cr_assert_not_null(str1);
    cr_assert_not_null(str2);
    ice_memcpy(str1, str2, 10);
    for (int i = 0 ; i < 10 ; i++)
        cr_assert_eq(str1[i], str2[i]);
    ice_memset(str1, 'a', 10);
    ice_memcpy(str2, str1, 10);
    for (int i = 0 ; i < 10 ; i++)
        cr_assert_eq(str1[i], str2[i]);
    ice_memset(str1, 'b', 10);
    ice_memcpy(str2, str1, 5);
    for (int i = 0 ; i < 5 ; i++)
        cr_assert_eq(str1[i], str2[i]);
    for (int i = 5 ; i < 10 ; i++)
        cr_assert_eq(str1[i], 'b');
    ice_memcpy(str2, str1, 1);
    cr_assert_eq(str1[0], str2[0]);
    cr_assert_eq(str1[1], 'b');
    ice_memcpy(str2, str1, 0);
    cr_assert_eq(str1[0], str2[0]);
    cr_assert_eq(str1[1], 'b');
    free(str1);
    free(str2);
}

Test(ice_realloc, basic)
{
    char *str = ice_calloc(10, sizeof(char));

    cr_assert_not_null(str);
    ice_memset(str, 'a', 10);
    str = ice_realloc(str, 20);
    cr_assert_not_null(str);
    for (int i = 0 ; i < 10 ; i++)
        cr_assert_eq(str[i], 'a');
    free(str);
}
