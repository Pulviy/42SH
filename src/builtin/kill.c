/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** kill_builtin
*/

#include "mysh.h"

int kill_pid(shell_t *shell)
{
    int atoi_result = atoi(shell->cmd_heap->argv[1]);

    if (atoi_result == 0 || atoi_result == -1)
        return (0);
    kill(atoi_result, SIGINT);
    return (0);
}

int kill_jobs(shell_t *shell)
{
    size_t index = 0;
    size_t len = strlen(shell->cmd_heap->argv[1]);
    int nb_job = 0;
    char *new = malloc(sizeof(char) * len);

    new[len - 1] = '\0';
    while (new[index] != '\0' || shell->cmd_heap->argv[1][index + 1] != '\0') {
        new[index] = shell->cmd_heap->argv [1][index + 1];
        ++index;
    }
    dprintf(1, "new:%s\n", new);
    if ((nb_job = atoi(new)) == 0 || nb_job == -1)
        return (0);
    dprintf(1, "here_atoi:%d\n", nb_job);
    while (shell->jobs != NULL) {
        if (shell->jobs->job_nb == nb_job)
            kill(shell->jobs->pid, SIGINT);
        shell->jobs = shell->jobs->next;
    }
    free(new);
    return (0);
}

int builtin_kill(shell_t *shell)
{
    pid_t pid = 0;
    int error = 0;

    if (!shell->cmd_heap->argv[0] || !shell->cmd_heap->argv[1] || \
strcmp(shell->cmd_heap->argv[0], "kill"))
        return (0);
    if (shell->cmd_heap->argv[1][0] == '%')
        error = kill_jobs(shell);
    else if ((pid = atoi(shell->cmd_heap->argv[1])) != 0)
        error = kill_pid(shell);
    if (error != 0)
        return (0);
    return (1);
}
