/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** repeat
*/

#include "mysh.h"

static int repeat_error_handling(shell_t *shell)
{
    if (shell->cmd_heap->argc < 3) {
        dprintf(2, "%s: Too few arguments.\n", shell->cmd_heap->argv[0]);
        return (0);
    }
    return (1);
}

int builtin_repeat(shell_t *shell)
{
    int repeat_number;
    int counter = 0;

    if (strcmp(shell->cmd_heap->argv[0], "repeat"))
        return (0);
    if (!repeat_error_handling(shell))
        return (1);
    repeat_number = atoi(shell->cmd_heap->argv[1]);
    free(shell->cmd_heap->argv[0]);
    free(shell->cmd_heap->argv[1]);
    while (counter + 2 < shell->cmd_heap->argc) {
        shell->cmd_heap->argv[counter] = shell->cmd_heap->argv[counter + 2];
        counter++;
    }
    shell->cmd_heap->argv[counter] = 0;
    shell->cmd_heap->argc -= 2;
    for (int index = 0; index < repeat_number; index++)
        exec_cmd(shell, 0);
    return (1);
}