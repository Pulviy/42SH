/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** exit
*/

#include "mysh.h"

int builtin_exit(shell_t *shell)
{
    if (strcmp(shell->cmd_heap->argv[0], "exit"))
        return (0);
    shell->running = 0;
    if (shell->cmd_heap->argc > 1)
        shell->status = atoi(shell->cmd_heap->argv[1]) % 256;
    else
        shell->status = 0;
    dprintf(1, "exit\n");
    return (1);
}