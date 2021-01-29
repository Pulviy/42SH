/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** manage the fg builtin
*/

#include "mysh.h"

int put_last_process_fg(shell_t *shell)
{
    while (shell->jobs->next != NULL)
        shell->jobs = shell->jobs->next;
    kill(shell->jobs->pid, SIGCONT);
    return (0);
}

int choose_process_fg(shell_t *shell)
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
            kill(shell->jobs->pid, SIGCONT);
        shell->jobs = shell->jobs->next;
    }
    free(new);
    return (0);
}

int builtin_fg(shell_t *shell)
{
    if (!shell->cmd_heap->argv[0] || strcmp(shell->cmd_heap->argv[0], "fg"))
        return (0);
    if (shell->cmd_heap->argv[1] && shell->cmd_heap->argv[1][0] == '%')
        choose_process_fg(shell);
    else
        put_last_process_fg(shell);
    return (1);
}
