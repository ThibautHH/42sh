#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "ice/output.h"

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(ice_puts, stdout, .init = redirect_all_std) {
    char *str = "Hello World!";
    ice_puts(str);

    cr_assert_stdout_eq_str(str, "Hello World!");
}

Test(ice_perror, stderr, .init = redirect_all_std) {
    char *str = "Hello World!";
    ice_dputs(2, str);

    cr_assert_stderr_eq_str(str, "Hello World!");
}