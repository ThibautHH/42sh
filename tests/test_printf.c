#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include <stdio.h>

#include "ice/string.h"
#include "ice/printf.h"

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(ice_printf, basic, .init = redirect_all_std)
{
    const char *str = "Hello World!";
    ull_t len = ice_strlen(str);
    ull_t ret = ice_printf("Hello World!");

    cr_assert_stdout_eq_str(str, "Hello World!");
    cr_assert_eq(ret, len, "ice_printf() returned %lli instead of %lli", ret, len);
}

Test(ice_dprintf, basic, .init = redirect_all_std)
{
    const char *str = "Hello World!";
    ull_t len = ice_strlen(str);
    ull_t ret = ice_dprintf(1, "Hello World!");

    cr_assert_stdout_eq_str(str, "Hello World!");
    cr_assert_eq(ret, len, "ice_dprintf() returned %lli instead of %lli", ret, len);
}

Test(ice_asprintf, basic)
{
    const char *str = "Hello World!";
    size_t len = ice_strlen(str);
    char *ret = NULL;

    ice_asprintf(&ret, "Hello World!");
    cr_assert_str_eq(str, "Hello World!");
    cr_assert_eq(ice_strlen(ret), len, "ice_asprintf() returned %zu instead of %zu", ice_strlen(ret), len);
    free(ret);
}

Test(ice_printf, null, .init = redirect_all_std)
{
    ull_t ret = ice_printf(NULL);

    cr_assert_eq(ret, -1, "ice_printf() returned %lli instead of -1", ret);
}

Test(ice_printf, empty, .init = redirect_all_std)
{
    ull_t ret = ice_printf("");

    cr_assert_eq(ret, 0, "ice_printf() returned %lli instead of 0", ret);
}

Test(ice_printf, format, .init = redirect_all_std)
{
    const char *str = "Hello World!";
    ull_t len = ice_strlen(str);
    ull_t ret = ice_printf("%s", "Hello World!");

    cr_assert_stdout_eq_str("Hello World!", "Hello World!");
    cr_assert_eq(ret, len, "ice_printf() returned %lli instead of %lli", ret, len);
}

Test(ice_printf, format_null, .init = redirect_all_std)
{
    const char *str = "(null)";
    ull_t len = ice_strlen(str);
    ull_t ret = ice_printf("%s", NULL);

    cr_assert_stdout_eq_str(str, "(null)");
    cr_assert_eq(ret, len, "ice_printf() returned %lli instead of %lli", ret, len);
}

Test(ice_printf, format_empty, .init = redirect_all_std)
{
    ull_t ret = ice_printf("%s", "");

    cr_assert_eq(ret, 0, "ice_printf() returned %lli instead of 0", ret);
}

Test(ice_printf, format_int, .init = redirect_all_std)
{
    const char *str = "42";
    ull_t len = ice_strlen(str);
    ull_t ret = ice_printf("%d", 42);

    cr_assert_stdout_eq_str(str, "42");
    cr_assert_eq(ret, len, "ice_printf() returned %lli instead of %lli", ret, len);
}

Test(ice_printf, format_uint, .init = redirect_all_std)
{
    const char *str = "42";
    ull_t len = ice_strlen(str);
    ull_t ret = ice_printf("%u", 42);

    cr_assert_stdout_eq_str(str, "42");
    cr_assert_eq(ret, len, "ice_printf() returned %lli instead of %lli", ret, len);
}

Test(ice_printf, format_char, .init = redirect_all_std)
{
    const char *str = "A";
    ull_t len = ice_strlen(str);
    ull_t ret = ice_printf("%c", 'A');

    cr_assert_stdout_eq_str(str, "A");
    cr_assert_eq(ret, len, "ice_printf() returned %lli instead of %lli", ret, len);
}

Test(ice_printf, format_pointer, .init = redirect_all_std)
{
    char str[32] = {0};
    ull_t len = sprintf(str, "%p", ice_printf);
    ull_t ret = ice_printf("%p", ice_printf);

    cr_assert_stdout_eq_str(str);
    cr_assert_eq(ret, len, "ice_printf() returned %lli instead of %lli", ret, len);
}

Test(ice_printf, format_percent, .init = redirect_all_std)
{
    const char *str = "%";
    ull_t len = ice_strlen(str);
    ull_t ret = ice_printf("%%");

    cr_assert_stdout_eq_str(str, "%");
    cr_assert_eq(ret, len, "ice_printf() returned %lli instead of %lli", ret, len);
}

Test(ice_printf, format_len, .init = redirect_all_std)
{
    const char *str = "Hello World!";
    ull_t len = ice_strlen(str);
    ull_t ret = 0;
    ull_t *ptr = &ret;

    ice_printf("%s%n", str, ptr);
    cr_assert_eq(ret, len, "ice_printf() returned %lli instead of %lli", ret, len);
}

Test(ice_printf, format_len_null, .init = redirect_all_std)
{
    ull_t ret = 0;
    ull_t *ptr = NULL;

    ice_printf("%n", ptr);
    cr_assert_eq(ret, 0, "ice_printf() returned %lli instead of 0", ret);
}

Test(ice_printf, format_len_empty, .init = redirect_all_std)
{
    ull_t ret = 0;
    ull_t *ptr = &ret;

    ice_printf("%n", ptr);
    cr_assert_eq(ret, 0, "ice_printf() returned %lli instead of 0", ret);
}

Test(ice_printf, format_float, .init = redirect_all_std)
{
    const char *str = "42.000000";
    ull_t len = ice_strlen(str);
    ull_t ret = ice_printf("%f", 42.0);

    cr_assert_stdout_eq_str(str, "42.000000");
    cr_assert_eq(ret, len, "ice_printf() returned %lli instead of %lli", ret, len);
}

Test(ice_printf, format_precision, .init = redirect_all_std)
{
    const char *str = "42.000000";
    ull_t len = ice_strlen(str);
    ull_t ret = ice_printf("%.6f", 42.0);

    cr_assert_stdout_eq_str(str, "42.000000");
    cr_assert_eq(ret, len, "ice_printf() returned %lli instead of %lli", ret, len);
}

Test(ice_printf, format_width, .init = redirect_all_std)
{
    const char *str = "   42";
    ull_t len = ice_strlen(str);
    ull_t ret = ice_printf("%5d", 42);

    cr_assert_stdout_eq_str(str, "   42");
    cr_assert_eq(ret, len, "ice_printf() returned %lli instead of %lli", ret, len);
}

Test(ice_printf, format_width_precision, .init = redirect_all_std)
{
    const char *str = "42.000000";
    ull_t len = ice_strlen(str);
    ull_t ret = ice_printf("%5.6f", 42.0);

    cr_assert_stdout_eq_str(str, "42.000000");
    cr_assert_eq(ret, len, "ice_printf() returned %lli instead of %lli", ret, len);
}

Test(ice_printf, format_width_precision_zero, .init = redirect_all_std)
{
    const char *str = "42.000000";
    ull_t len = ice_strlen(str);
    ull_t ret = ice_printf("%05.6f", 42.0);

    cr_assert_stdout_eq_str(str, "42.000000");
    cr_assert_eq(ret, len, "ice_printf() returned %lli instead of %lli", ret, len);
}

Test(ice_printf, format_width_precision_zero_neg, .init = redirect_all_std)
{
    const char *str = "-42.000000";
    ull_t len = ice_strlen(str);
    ull_t ret = ice_printf("%05.6f", -42.0);

    cr_assert_stdout_eq_str(str, "-42.000000");
    cr_assert_eq(ret, len, "ice_printf() returned %lli instead of %lli", ret, len);
}

Test(ice_printf, format_width_precision_zero_neg_space, .init = redirect_all_std)
{
    const char *str = "-42.000000";
    ull_t len = ice_strlen(str);
    ull_t ret = ice_printf("% 5.6f", -42.0);

    cr_assert_stdout_eq_str(str, "-42.000000");
    cr_assert_eq(ret, len, "ice_printf() returned %lli instead of %lli", ret, len);
}

Test(ice_printf, format_width_precision_zero_neg_space_plus, .init = redirect_all_std)
{
    const char *str = "-42.000000";
    ull_t len = ice_strlen(str);
    ull_t ret = ice_printf("%+5.6f", -42.0);

    cr_assert_stdout_eq_str(str, "-42.000000");
    cr_assert_eq(ret, len, "ice_printf() returned %lli instead of %lli", ret, len);
}

Test(ice_printf, format_width_precision_zero_neg_space_plus_hash, .init = redirect_all_std)
{
    const char *str = "-42.000000";
    ull_t len = ice_strlen(str);
    ull_t ret = ice_printf("%+#5.6f", -42.0);

    cr_assert_stdout_eq_str(str, "-42.000000");
    cr_assert_eq(ret, len, "ice_printf() returned %lli instead of %lli", ret, len);
}

Test(ice_printf, format_width_precision_zero_neg_space_plus_hash_zero, .init = redirect_all_std)
{
    const char *str = "-42.000000";
    ull_t len = ice_strlen(str);
    ull_t ret = ice_printf("%0+#5.6f", -42.0);

    cr_assert_stdout_eq_str(str, "-42.000000");
    cr_assert_eq(ret, len, "ice_printf() returned %lli instead of %lli", ret, len);
}

Test(ice_printf, format_precision_low, .init = redirect_all_std)
{
    const char *str = "42.000";
    ull_t len = ice_strlen(str);
    ull_t ret = ice_printf("%.3f", 42.0);

    cr_assert_stdout_eq_str(str, "42.000");
    cr_assert_eq(ret, len, "ice_printf() returned %lli instead of %lli", ret, len);
}

Test(ice_printf, format_precision_high, .init = redirect_all_std)
{
    const char *str = "42.000000000";
    ull_t len = ice_strlen(str);
    ull_t ret = ice_printf("%.9f", 42.0);

    cr_assert_stdout_eq_str(str, "42.000000000");
    cr_assert_eq(ret, len, "ice_printf() returned %lli instead of %lli", ret, len);
}

Test(ice_printf, format_star, .init = redirect_all_std)
{
    const char *str = "42";
    ull_t len = ice_strlen(str);
    ull_t ret = ice_printf("%*d", 2, 42);

    cr_assert_stdout_eq_str(str, "42");
    cr_assert_eq(ret, len, "ice_printf() returned %lli instead of %lli", ret, len);
}

Test(ice_printf, format_star_neg, .init = redirect_all_std)
{
    const char *str = "42";
    ull_t len = ice_strlen(str);
    ull_t ret = ice_printf("%*d", -2, 42);

    cr_assert_stdout_eq_str(str, "42");
    cr_assert_eq(ret, len, "ice_printf() returned %lli instead of %lli", ret, len);
}

Test(ice_printf, format_star_neg_prec, .init = redirect_all_std)
{
    const char *str = "42";
    ull_t len = ice_strlen(str);
    ull_t ret = ice_printf("%.*d", -2, 42);

    cr_assert_stdout_eq_str(str, "42");
    cr_assert_eq(ret, len, "ice_printf() returned %lli instead of %lli", ret, len);
}

Test(ice_printf, format_star_neg_prec_zero, .init = redirect_all_std)
{
    const char *str = "42";
    ull_t len = ice_strlen(str);
    ull_t ret = ice_printf("%0.*d", -2, 42);

    cr_assert_stdout_eq_str(str, "42");
    cr_assert_eq(ret, len, "ice_printf() returned %lli instead of %lli", ret, len);
}

Test(ice_printf, format_width_char, .init = redirect_all_std)
{
    const char *str = "    4";
    ull_t len = ice_strlen(str);
    ull_t ret = ice_printf("%5c", '4');

    cr_assert_stdout_eq_str(str, "    4");
    cr_assert_eq(ret, len, "ice_printf() returned %lli instead of %lli", ret, len);
}

Test(ice_printf, format_binary, .init = redirect_all_std)
{
    const char *str = "101010";
    ull_t len = ice_strlen(str);
    ull_t ret = ice_printf("%b", 42);

    cr_assert_stdout_eq_str(str, "101010");
    cr_assert_eq(ret, len, "ice_printf() returned %lli instead of %lli", ret, len);
}

Test(ice_printf, format_octal, .init = redirect_all_std)
{
    const char *str = "52";
    ull_t len = ice_strlen(str);
    ull_t ret = ice_printf("%o", 42);

    cr_assert_stdout_eq_str(str, "52");
    cr_assert_eq(ret, len, "ice_printf() returned %lli instead of %lli", ret, len);
}

Test(ice_printf, format_hexa, .init = redirect_all_std)
{
    const char *str = "2a";
    ull_t len = ice_strlen(str);
    ull_t ret = ice_printf("%x", 42);

    cr_assert_stdout_eq_str(str, "2a");
    cr_assert_eq(ret, len, "ice_printf() returned %lli instead of %lli", ret, len);
}

Test(ice_printf, format_hexa_upper, .init = redirect_all_std)
{
    const char *str = "2A";
    ull_t len = ice_strlen(str);
    ull_t ret = ice_printf("%X", 42);

    cr_assert_stdout_eq_str(str, "2A");
    cr_assert_eq(ret, len, "ice_printf() returned %lli instead of %lli", ret, len);
}

Test(ice_printf, format_noexist, .init = redirect_all_std)
{
    ull_t ret = ice_printf("%z");

    cr_assert_eq(ret, 0, "ice_printf() returned %lli instead of 0", ret);
}

Test(ice_printf, format_octal_hash, .init = redirect_all_std)
{
    const char *str = "052";
    ull_t len = ice_strlen(str);
    ull_t ret = ice_printf("%#o", 42);

    cr_assert_stdout_eq_str(str, "052");
    cr_assert_eq(ret, len, "ice_printf() returned %lli instead of %lli", ret, len);
}

Test(ice_printf, format_hexa_hash, .init = redirect_all_std)
{
    const char *str = "0x2a";
    ull_t len = ice_strlen(str);
    ull_t ret = ice_printf("%#x", 42);

    cr_assert_stdout_eq_str(str, "0x2a");
    cr_assert_eq(ret, len, "ice_printf() returned %lli instead of %lli", ret, len);
}

Test(ice_printf, format_hexa_upper_hash, .init = redirect_all_std)
{
    const char *str = "0X2A";
    ull_t len = ice_strlen(str);
    ull_t ret = ice_printf("%#X", 42);

    cr_assert_stdout_eq_str(str, "0X2A");
    cr_assert_eq(ret, len, "ice_printf() returned %lli instead of %lli", ret, len);
}

Test(ice_printf, format_binary_hash, .init = redirect_all_std)
{
    const char *str = "0b101010";
    ull_t len = ice_strlen(str);
    ull_t ret = ice_printf("%#b", 42);

    cr_assert_stdout_eq_str(str, "0b101010");
    cr_assert_eq(ret, len, "ice_printf() returned %lli instead of %lli", ret, len);
}

Test(ice_printf, format_int_space, .init = redirect_all_std)
{
    const char *str = " 42";
    ull_t len = ice_strlen(str);
    ull_t ret = ice_printf("% d", 42);

    cr_assert_stdout_eq_str(str, " 42");
    cr_assert_eq(ret, len, "ice_printf() returned %lli instead of %lli", ret, len);
}

Test(ice_printf, format_int_plus, .init = redirect_all_std)
{
    const char *str = "+42";
    ull_t len = ice_strlen(str);
    ull_t ret = ice_printf("%+d", 42);

    cr_assert_stdout_eq_str(str, "+42");
    cr_assert_eq(ret, len, "ice_printf() returned %lli instead of %lli", ret, len);
}

Test(ice_printf, format_float_space, .init = redirect_all_std)
{
    const char *str = " 42.000000";
    ull_t len = ice_strlen(str);
    ull_t ret = ice_printf("% f", 42.0);

    cr_assert_stdout_eq_str(str, " 42.000000");
    cr_assert_eq(ret, len, "ice_printf() returned %lli instead of %lli", ret, len);
}

Test(ice_printf, format_float_plus, .init = redirect_all_std)
{
    const char *str = "+42.000000";
    ull_t len = ice_strlen(str);
    ull_t ret = ice_printf("%+f", 42.0);

    cr_assert_stdout_eq_str(str, "+42.000000");
    cr_assert_eq(ret, len, "ice_printf() returned %lli instead of %lli", ret, len);
}

Test(ice_printf, format_string_precision, .init = redirect_all_std)
{
    const char *str = "42";
    ull_t len = ice_strlen(str);
    ull_t ret = ice_printf("%.2s", "42");

    cr_assert_stdout_eq_str(str, "42");
    cr_assert_eq(ret, len, "ice_printf() returned %lli instead of %lli", ret, len);
}

Test(ice_printf, format_string_precision_bigest, .init = redirect_all_std)
{
    const char *str = "42";
    ull_t len = ice_strlen(str);
    ull_t ret = ice_printf("%.42s", "42");

    cr_assert_stdout_eq_str(str, "42");
    cr_assert_eq(ret, len, "ice_printf() returned %lli instead of %lli", ret, len);
}

Test(ice_printf, format_zero_minuse, .init = redirect_all_std)
{
    const char *str = "-42";
    ull_t len = ice_strlen(str);
    ull_t ret = ice_printf("%0-d", -42);

    cr_assert_stdout_eq_str(str, "-42");
    cr_assert_eq(ret, len, "ice_printf() returned %lli instead of %lli", ret, len);
}

Test(ice_printf, format_space_plus, .init = redirect_all_std)
{
    const char *str = "+42";
    ull_t len = ice_strlen(str);
    ull_t ret = ice_printf("% +d", 42);

    cr_assert_stdout_eq_str(str, "+42");
    cr_assert_eq(ret, len, "ice_printf() returned %lli instead of %lli", ret, len);
}

Test(ice_printf, format_zero, .init = redirect_all_std)
{
    const char *str = "00000042";
    ull_t len = ice_strlen(str);
    ull_t ret = ice_printf("%08d", 42);

    cr_assert_stdout_eq_str(str, "00000042");
    cr_assert_eq(ret, len, "ice_printf() returned %lli instead of %lli", ret, len);
}

Test(ice_asprintf, format_null, .init = redirect_all_std)
{
    char *str = NULL;
    const char *expected = "42";
    ull_t len = ice_strlen(expected);
    ull_t ret = ice_asprintf(&str, "%d", 42);

    cr_assert_str_eq(str, expected, "ice_asprintf() returned %s instead of %s", str, expected);
    cr_assert_eq(ret, len, "ice_asprintf() returned %lli instead of %lli", ret, len);
}

Test(ice_asprintf, format_string_null, .init = redirect_all_std)
{
    char *str = NULL;
    ull_t ret = ice_asprintf(&str, NULL);

    cr_assert_null(str, "ice_asprintf() returned %s instead of NULL", str);
    cr_assert_eq(ret, -1, "ice_asprintf() returned %lli instead of -1", ret);
}

Test(ice_sprintf, format_int, .init = redirect_all_std)
{
    char str[100];
    const char *expected = "42";
    ull_t len = ice_strlen(expected);
    ull_t ret = ice_sprintf(str, "%d", 42);

    cr_assert_str_eq(str, expected, "ice_sprintf() returned %s instead of %s", str, expected);
    cr_assert_eq(ret, len, "ice_sprintf() returned %lli instead of %lli", ret, len);
}

Test(ice_snprintf, format_int, .init = redirect_all_std)
{
    char str[100];
    const char *expected = "42";
    ull_t len = ice_strlen(expected);
    ull_t ret = ice_snprintf(str, 100, "%d", 42);

    cr_assert_str_eq(str, expected, "ice_snprintf() returned %s instead of %s", str, expected);
    cr_assert_eq(ret, len, "ice_snprintf() returned %lli instead of %lli", ret, len);
}
