#include <criterion/criterion.h>

#include "ice/int.h"

Test(ice_intlen, digit) {
    int result = ice_intlen(7);

    cr_assert_eq(result, 1, "Digit should be handled, get %d", result);
}

Test(ice_intlen, zero) {
    int result = ice_intlen(0);

    cr_assert_eq(result, 1, "Zero should be handled, get %d", result);
}

Test(ice_intlen, negative_digit) {
    int result = ice_intlen(-3);

    cr_assert_eq(result, 2, "Negative digit should be handled, get %d", result);
}

Test(ice_intlen, max_long_long) {
    int result = ice_intlen(9223372036854775807);

    cr_assert_eq(result, 19, "Max long long should be handled, get %d", result);
}

Test(ice_intlen, min_long_long) {
    int result = ice_intlen(-9223372036854775807);

    cr_assert_eq(result, 20, "Min long long should be handled, get %d", result);
}

Test(ice_atoi, digit_to_int) {
    int result = (int)ice_atoi("7");

    cr_assert_eq(result, 7, "Digit should be handled, get %d", result);
}

Test(ice_atoi, zero_to_int) {
    int result = (int)ice_atoi("0");

    cr_assert_eq(result, 0, "Zero should be handled, get %d", result);
}

Test(ice_atoi, negative_digit_to_int) {
    int result = (int)ice_atoi("-3");

    cr_assert_eq(result, -3, "Negative digit should be handled, get %d", result);
}

Test(ice_atoi, max_long_long_to_int) {
    long long result = ice_atoi("9223372036854775807");

    cr_assert_eq(result, 9223372036854775807, "Max long long should be handled, get %lli", result);
}

Test(ice_atoi, min_long_long_to_int) {
    long long result = ice_atoi("-9223372036854775807");

    cr_assert_eq(result, -9223372036854775807, "Min long long should be handled, get %lli", result);
}

Test(ice_itoa, digit_to_array) {
    char buffer[11];

    ice_itoa(7, buffer);

    cr_assert_str_eq(buffer, "7", "Digit should be handled, get %s", buffer);
}

Test(ice_itoa, zero_to_array) {
    char buffer[11];

    ice_itoa(0, buffer);

    cr_assert_str_eq(buffer, "0", "Zero should be handled, get %s", buffer);
}

Test(ice_itoa, negative_digit_to_array) {
    char buffer[11];

    ice_itoa(-3, buffer);

    cr_assert_str_eq(buffer, "-3", "Negative digit should be handled, get %s", buffer);
}


Test(ice_itoa, max_long_long_to_array) {
    char buffer[20];

    ice_itoa(9223372036854775807, buffer);

    cr_assert_str_eq(buffer, "9223372036854775807", "Max long long should be handled, get %s", buffer);
}

Test(ice_itoa, min_long_long_to_array) {
    char buffer[20];

    ice_itoa(-9223372036854775807, buffer);

    cr_assert_str_eq(buffer, "-9223372036854775807", "Min long long should be handled, get %s", buffer);
}

Test(ice_strtol, digit_to_long) {
    char *endptr;
    long result = ice_strtol("7", &endptr);

    cr_assert_eq(result, 7, "Digit should be handled, get %ld", result);
    cr_assert_str_eq(endptr, "", "Endptr should be empty, get %s", endptr);
}

Test(ice_strtol, zero_to_long) {
    char *endptr;
    long result = ice_strtol("0", &endptr);

    cr_assert_eq(result, 0, "Zero should be handled, get %ld", result);
    cr_assert_str_eq(endptr, "", "Endptr should be empty, get %s", endptr);
}

Test(ice_strtol, negative_digit_to_long) {
    char *endptr;
    long result = ice_strtol("-3", &endptr);

    cr_assert_eq(result, -3, "Negative digit should be handled, get %ld", result);
    cr_assert_str_eq(endptr, "", "Endptr should be empty, get %s", endptr);
}

Test(ice_strtol, max_long_long_to_long) {
    char *endptr;
    long result = ice_strtol("9223372036854775807", &endptr);

    cr_assert_eq(result, 9223372036854775807, "Max long long should be handled, get %ld", result);
    cr_assert_str_eq(endptr, "", "Endptr should be empty, get %s", endptr);
}

Test(ice_strtol, min_long_long_to_long) {
    char *endptr;
    long result = ice_strtol("-9223372036854775807", &endptr);

    cr_assert_eq(result, -9223372036854775807, "Min long long should be handled, get %ld", result);
    cr_assert_str_eq(endptr, "", "Endptr should be empty, get %s", endptr);
}

Test(ice_strtol, digit_to_long_with_endptr) {
    char *endptr;
    long result = ice_strtol("7abc", &endptr);

    cr_assert_eq(result, 7, "Digit should be handled, get %ld", result);
    cr_assert_str_eq(endptr, "abc", "Endptr should be empty, get %s", endptr);
}
