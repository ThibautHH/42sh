/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** mysh.c
*/

#include "mysh.h"

int main(int ac, UNUSED char **av, char **env)
{
    mysh_t context = {0};
    if (ac != 1)
        return 1;
    mysh(&context, env);
    return context.status;
}
