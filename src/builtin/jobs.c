/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** File which manage the jobs for our shell
*/

#include "mysh.h"

void sig_tstp(int sig_num)
{
    if (sig_num == SIGTSTP)
        dprintf(1, "sigtstp\n");
}

int print_job(int job_nb, char *status, char *name)
{
    if (dprintf(1, "[%d]  %s  %s\n", job_nb, status, name) < 0)
        return (-1);
    return (0);
}

int builtin_jobs(shell_t *shell)
{
    if (!shell->cmd_heap->argv[0] || strcmp(shell->cmd_heap->argv[0], "jobs"))
        return (0);
    while (shell->jobs != NULL) {
        if (print_job(shell->jobs->job_nb, shell->jobs->status, \
            shell->jobs->name) == -1)
            return (0);
        shell->jobs = shell->jobs->next;
    }
    return (1);
}
