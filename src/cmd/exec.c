/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** cmd
*/

#include "mysh.h"

int exec_builtin(shell_t *shell, int from_pipe);

void exec_cmd_heap(shell_t *shell)
{
    int save[2];

    save[0] = dup(0);
    save[1] = dup(1);
    while (shell->cmd_heap) {
        redirect_fds(shell, save);
        if (!create_pipes(shell)) {
            check_separators(shell);
        }
    }
    dup2(save[0], 0);
    dup2(save[1], 1);
}

int exec_cmd(shell_t *shell, int from_pipe)
{
    int stopper = 0;

    stopper = (!stopper ? exec_builtin(shell, from_pipe) : stopper);
    stopper = (!stopper ? exec_bin(shell, !from_pipe) : stopper);
    if (stopper == 0) {
        dprintf(2, "%s: Command not found.\n", *shell->cmd_heap->argv);
        shell->status = 1;
    }
    if (stopper == 2) {
        dprintf(2, "%s: Permission denied.\n", *shell->cmd_heap->argv);
        shell->status = 1;
    } else if (stopper == 3) {
        dprintf(2, "%s: Exec format error. Wrong Architecture.\n", \
        *shell->cmd_heap->argv);
        shell->status = 1;
    }
    return (stopper);
}

void wait_child(shell_t *shell, int child_pid)
{
    int child_status = 0;
    char *err_msg = NULL;
    int termsig = 0;

    waitpid(child_pid, &child_status, 0);
    termsig = WTERMSIG(child_status);
    err_msg = strsignal(termsig);
    if (err_msg && !strcmp(err_msg, "Floating point exception"))
        err_msg = "Floating exception";
    if (termsig && !WCOREDUMP(child_status))
        dprintf(2, "%s\n", err_msg);
    else if (termsig)
        dprintf(2, "%s (core dumped)\n", err_msg);
    if (!WIFEXITED(child_status))
        shell->status = termsig;
    else
        shell->status = WEXITSTATUS(child_status);
}

int exec_bin(shell_t *shell, int need_fork)
{
    char *binpath = locate_bin(shell, shell->cmd_heap->argv[0]);
    pid_t pid;

    if (binpath == NULL)
        return (0);
    if (!is_file(binpath) || access(binpath, X_OK) != 0)
        return (2);
    pid = (need_fork ? fork() : 0);
    if (pid == -1) {
        perror("fork");
    } else if (!need_fork || pid == 0) {
        execve(binpath, shell->cmd_heap->argv, shell->env_arr);
    } else {
        wait_child(shell, pid);
    }
    free(binpath);
    return (1);
}
