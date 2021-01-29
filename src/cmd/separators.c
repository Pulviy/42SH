/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** check separators before executing a cmd
*/

#include "mysh.h"

int check_separators(shell_t *shell)
{
    if (!shell->cmd_heap->is_or && !shell->cmd_heap->is_and) {
        exec_cmd(shell, 0);
        list_pop((void **)&(shell->cmd_heap), shell->cmd_heap);
        return (0);
    }
    if (shell->cmd_heap->is_and == 1 && shell->status == 0) {
        exec_cmd(shell, 0);
        list_pop((void **)&(shell->cmd_heap), shell->cmd_heap);
    } else if (shell->cmd_heap->is_or == 1 && shell->status != 0) {
        exec_cmd(shell, 0);
        list_pop((void **)&(shell->cmd_heap), shell->cmd_heap);
    } else
        list_pop((void **)&(shell->cmd_heap), shell->cmd_heap);
    return (0);
}