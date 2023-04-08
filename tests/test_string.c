#include <criterion/criterion.h>

#include "ice/string.h"

Test(ice_strlen, basic) {
    char *str = "Hello World!";
    unsigned long long len = ice_strlen(str);

    cr_assert_eq(len, 12, "ice_strlen() returned %lli instead of 12", len);
}

Test(ice_strlen, null) {
    char *str = NULL;
    unsigned long long len = ice_strlen(str);

    cr_assert_eq(len, 0, "ice_strlen() returned %lli instead of 0", len);
}

Test(ice_strlen, empty) {
    char *str = "";
    unsigned long long len = ice_strlen(str);

    cr_assert_eq(len, 0, "ice_strlen() returned %lli instead of 0", len);
}

Test(ice_strcpy, basic) {
    char str1[15] = {0};
    char str2[] = "Hello World!";

    ice_strcpy(str1, str2);

    cr_assert_str_eq(str1, str2, "ice_strcpy() returned %s instead of Hello World!", str1);
}

Test(ice_strncpy, basic) {
    char str1[15] = {0};
    char str2[] = "Hello World!";

    ice_strncpy(str1, str2, 5);

    cr_assert_str_eq(str1, "Hello", "ice_strncpy() returned %s instead of Hello World!", str1);
}

Test(ice_strcat, basic) {
    char str1[15] = {0};
    char str2[] = " World!";

    ice_strcpy(str1, "Hello");
    ice_strcat(str1, str2);

    cr_assert_str_eq(str1, "Hello World!", "ice_strcat() returned %s instead of Hello World!", str1);
}

Test(ice_strncat, basic) {
    char str1[15] = {0};
    char str2[] = " World!";

    ice_strcpy(str1, "Hello");
    ice_strncat(str1, str2, 6);

    cr_assert_str_eq(str1, "Hello World", "ice_strncat() returned %s instead of Hello World!", str1);
}

Test(ice_strcmp, basic) {
    char res = ice_strcmp("Hello World!", "Hello World!");

    cr_assert_eq(res, 0, "ice_strcmp() returned %i instead of 0", res);
}

Test(ice_strcmp, different_higher) {
    char res = ice_strcmp("Hello World!", "Hello World");

    cr_assert_eq(res, 33, "ice_strcmp() returned %i instead of 33", res);
}

Test(ice_strcmp, different_lower) {
    char res = ice_strcmp("Hello World", "Hello World!");

    cr_assert_eq(res, -33, "ice_strcmp() returned %i instead of -33", res);
}

Test(ice_strcmp, different_lower_and_same_size) {
    char res = ice_strcmp("Hello World!", "Hello World?");

    cr_assert_eq(res, -30, "ice_strcmp() returned %i instead of -30", res);
}

Test(ice_strncmp, basic) {
    int res = ice_strncmp("Hello World!", "Hello World!", 12);

    cr_assert_eq(res, 0, "ice_strncmp() returned %i instead of 0", res);
}

Test(ice_strncmp, same_with_n) {
    int res = ice_strncmp("Hello World!", "Hello World", 11);

    cr_assert_eq(res, 0, "ice_strncmp() returned %i instead of 0", res);
}

Test(ice_strncmp, different_lower_and_same_size) {
    int res = ice_strncmp("Hello World!", "Hello World?", 11);

    cr_assert_eq(res, 0, "ice_strncmp() returned %i instead of 0", res);
}

Test(ice_strncmp, different_lower_and_same_size_and_n_equal_size) {
    int res = ice_strncmp("Hello World!", "Hello World?", 12);

    cr_assert_eq(res, -30, "ice_strncmp() returned %i instead of -30", res);
}

Test(ice_strncmp, different_higher_and_same_size_and_n_equal_size) {
    int res = ice_strncmp("Hello World?", "Hello World!", 12);

    cr_assert_eq(res, 30, "ice_strncmp() returned %i instead of 30", res);
}

Test(ice_strncmp, different_lower_and_same_size_and_n_higher_size) {
    int res = ice_strncmp("Hello World!", "Hello World?", 13);

    cr_assert_eq(res, -30, "ice_strncmp() returned %i instead of -30", res);
}

Test(ice_strncmp, different_higher_and_same_size_and_n_higher_size) {
    int res = ice_strncmp("Hello World?", "Hello World!", 13);

    cr_assert_eq(res, 30, "ice_strncmp() returned %i instead of 30", res);
}

Test(ice_strncmp, different_lower_and_same_size_and_n_lower_size) {
    int res = ice_strncmp("Hello World!", "Hello World!", 12);

    cr_assert_eq(res, 0, "ice_strncmp() returned %i instead of 0", res);
}

Test(ice_strdup, basic) {
    char *str = ice_strdup("Hello World!");

    cr_assert_str_eq(str, "Hello World!", "ice_strdup() returned %s instead of Hello World!", str);
    free(str);
}

Test(ice_strdup, null) {
    char *str = ice_strdup(NULL);

    cr_assert_null(str, "ice_strdup() returned %s instead of NULL", str);
}

Test(ice_strdup, empty) {
    char *str = ice_strdup("");

    cr_assert_str_eq(str, "", "ice_strdup() returned %s instead of \"\"", str);
    free(str);
}

Test(ice_strndup, basic) {
    char *str = ice_strndup("Hello World!", 5);

    cr_assert_str_eq(str, "Hello", "ice_strndup() returned %s instead of Hello World!", str);
    free(str);
}

Test(ice_strndup, null) {
    char *str = ice_strndup(NULL, 5);

    cr_assert_null(str, "ice_strndup() returned %s instead of NULL", str);
}

Test(ice_strndup, empty) {
    char *str = ice_strndup("", 5);

    cr_assert_str_eq(str, "", "ice_strndup() returned %s instead of \"\"", str);
    free(str);
}

Test(ice_strswap, basic) {
    char str[] = "Hello World!";

    ice_strswap(str, 1, 4);

    cr_assert_str_eq(str, "Holle World!", "ice_strswap() returned %s instead of Holle World!", str);
}

Test(ice_strrev, basic) {
    char str[] = "Hello World!";

    ice_strrev(str);

    cr_assert_str_eq(str, "!dlroW olleH", "ice_strrev() returned %s instead of !dlroW olleH", str);
}

Test(ice_strrev, empty) {
    char str[] = "";

    ice_strrev(str);

    cr_assert_str_eq(str, "", "ice_strrev() returned %s instead of \"\"", str);
}

Test(ice_strrev, one_char) {
    char str[] = "a";

    ice_strrev(str);

    cr_assert_str_eq(str, "a", "ice_strrev() returned %s instead of \"a\"", str);
}

Test(ice_strnrev, basic) {
    char str[] = "Hello World!";

    ice_strnrev(str, 4);

    cr_assert_str_eq(str, "olleH World!", "ice_strnrev() returned %s instead of olleH World!", str);
}

Test(ice_strnrev, empty) {
    char str[] = "";

    ice_strnrev(str, 5);

    cr_assert_str_eq(str, "", "ice_strnrev() returned %s instead of \"\"", str);
}

Test(ice_strnrev, one_char) {
    char str[] = "a";

    ice_strnrev(str, 5);

    cr_assert_str_eq(str, "a", "ice_strnrev() returned %s instead of \"a\"", str);
}

Test(ice_strsplit, basic) {
    char **str = ice_strsplit("Hello World!", " ");

    cr_assert_str_eq(str[0], "Hello", "ice_strsplit() returned %s instead of Hello", str[0]);
    cr_assert_str_eq(str[1], "World!", "ice_strsplit() returned %s instead of World!", str[1]);
    cr_assert_null(str[2], "ice_strsplit() returned %s instead of NULL", str[2]);

    free(str[0]);
    free(str[1]);
    free(str);
}

Test(ice_strsplit, empty) {
    char **str = ice_strsplit("", " ");

    cr_assert_str_eq(str[0], "", "ice_strsplit() returned %s instead of \"\"", str[0]);

    free(str);
}

Test(ice_strstr, basic) {
    char *str = ice_strstr("Hello World!", "World");

    cr_assert_str_eq(str, "World!", "ice_strstr() returned %s instead of World!", str);
}

Test(ice_strstr, empty) {
    char *str = ice_strstr("", "World");

    cr_assert_null(str, "ice_strstr() returned %s instead of NULL", str);
}

Test(ice_strchr, basic) {
    char *str = ice_strchr("Hello World!", 'W');

    cr_assert_str_eq(str, "World!", "ice_strchr() returned %s instead of World!", str);
}

Test(ice_strchr, empty) {
    char *str = ice_strchr("", 'W');

    cr_assert_null(str, "ice_strchr() returned %s instead of NULL", str);
}

Test(ice_strtrim, basic) {
    char str[] = "   \t Hello World! \t  ";

    ice_strtrim(str);
    cr_assert_str_eq(str, "Hello World!");
}

Test(ice_strtrim, empty) {
    char str[] = "";

    ice_strtrim(str);
    cr_assert_str_eq(str, "");
}
