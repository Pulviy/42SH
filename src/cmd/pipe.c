/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** pipe
*/

#include "mysh.h"

int exec_pipe(int *fds, int nmemb, int index, shell_t *shell)
{
    int index_close = 0;
    int status = 0;

    if (fork() == 0) {
        if (index > 0)
            dup2(fds[(index - 1) * 2], 0);
        if (index < (nmemb - 1))
            dup2(fds[index * 2 + 1], 1);
        if (shell->cmd_heap->out != 1)
            dup2(shell->cmd_heap->out, 1);
        while (index_close < (nmemb - 1) * 2)
            close(fds[index_close++]);
        status = exec_cmd(shell, 1);
    } else if (index < nmemb - 1) {
        list_pop((void **)&(shell->cmd_heap), shell->cmd_heap);
        status = exec_pipe(fds, nmemb, index + 1, shell);
    }
    return (status);
}

int count_pipes(shell_t *shell)
{
    int nmemb = 1;
    instr_t *tmp = shell->cmd_heap->next;

    while (tmp && tmp->is_pipe) {
        tmp = tmp->next;
        nmemb++;
    }
    return (nmemb);
}

int create_pipes(shell_t *shell)
{
    int nmemb = count_pipes(shell);
    int fds[(nmemb - 1) * 2];
    int status;
    int index = 0;
    int index_close = 0;

    if (nmemb <= 1)
        return (0);
    while (index * 2 < (nmemb - 1) * 2)
        pipe(fds + (index++ * 2));
    exec_pipe(fds, nmemb, 0, shell);
    list_pop((void **)&(shell->cmd_heap), shell->cmd_heap);
    while (index_close < (nmemb - 1) * 2)
        close(fds[index_close++]);
    index = 0;
    while (index < nmemb) {
        wait(&status);
        ++index;
    }
    return (nmemb);
}