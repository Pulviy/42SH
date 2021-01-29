/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** echo
*/

#include "mysh.h"


int builtin_echo(shell_t *shell)
{
    int index = 1;
    int newline = 1;

    if (strcmp(shell->cmd_heap->argv[0], "echo"))
        return (0);
    if (shell->cmd_heap->argv[1] && !strcmp(shell->cmd_heap->argv[1], "-n")) {
        newline = 0;
        ++index;
    }
    while (index < shell->cmd_heap->argc) {
        dprintf(1, shell->cmd_heap->argv[index]);
        if (index < shell->cmd_heap->argc - 1)
            dprintf(1, " ");
        ++index;
    }
    if (newline)
        dprintf(1, "\n");
    return (1);
}