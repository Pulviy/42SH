/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** manage the '&' sign at the end of line, to put process in jobs 
** list and in background
*/

#include "mysh.h"

int exec_jobs_process(shell_t *shell, pid_t *pid)
{
    char *binpath = locate_bin(shell, shell->cmd_heap->argv[0]);

    if (binpath == NULL)
        return (0);
    if (!is_file(binpath) || access(binpath, X_OK) != 0)
        return (2);
    *pid = fork();
    if (*pid == -1)
        perror("fork");
    execve(binpath, shell->cmd_heap->argv, shell->env_arr);
    kill(*pid, SIGSTOP);
    free(binpath);
    return (1);
}

int add_jobs_list(jobs_t *jobs, pid_t pid, char *name, char *status)
{
    jobs_t *new = malloc(sizeof(jobs_t));

    if (!new)
        return (84);
    new->next = NULL;
    if (!jobs) {
        new->prev = NULL;
        jobs = new;
    } else {
        while (jobs->next)
            jobs = jobs->next;
        new->prev = jobs;
    }
    new->name = name;
    new->status = status;
    new->pid = pid;
    return (0);
}

int builtin_process_bg(shell_t *shell)
{
    pid_t pid = 0;
    size_t index = 0;

    if (!shell->cmd_heap->argv[0])
        return (0);
    while (shell->cmd_heap->argv[index + 1])
        ++index;
    if (strcmp(shell->cmd_heap->argv[index], "&"))
        return (0);
    exec_jobs_process(shell, &pid);
    add_jobs_list(shell->jobs, pid, "suspended", shell->cmd_heap->argv[0]);
    return (1);
}
