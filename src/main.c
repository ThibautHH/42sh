/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** mysh.c
*/

#include "mysh.h"

int main(UNUSED int ac, char **av, char **env)
{
    mysh_t context = {0};

    handle_shebang_invocation(av);
    mysh(&context, env);
    return context.status;
}
