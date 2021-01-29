/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** exec_builtins
*/

#include "mysh.h"

static int do_builtins(shell_t *shell)
{
    int stopper = 0;

    stopper = (!stopper ? builtin_alias(shell) : stopper);
    stopper = (!stopper ? builtin_cd(shell) : stopper);
    stopper = (!stopper ? builtin_env(shell) : stopper);
    stopper = (!stopper ? builtin_setenv(shell) : stopper);
    stopper = (!stopper ? builtin_unsetenv(shell) : stopper);
    stopper = (!stopper ? builtin_which(shell) : stopper);
    stopper = (!stopper ? builtin_where(shell) : stopper);
    stopper = (!stopper ? builtin_echo(shell) : stopper);
    stopper = (!stopper ? builtin_repeat(shell) : stopper);
    stopper = (!stopper ? builtin_export(shell) : stopper);
    stopper = (!stopper ? builtin_unset(shell) : stopper);
    stopper = (!stopper ? builtin_exit(shell) : stopper);
    stopper = (!stopper ? builtin_kill(shell) : stopper);
    stopper = (!stopper ? builtin_process_bg(shell) : stopper);
    stopper = (!stopper ? builtin_fg(shell) : stopper);
    return (stopper);
}

int exec_builtin(shell_t *shell, int from_pipe)
{
    int stopper = 0;

    if (!shell->cmd_heap->argv[0])
        return (0);
    stopper = do_builtins(shell);
    if (stopper && from_pipe)
        exit(shell->status);
    return (stopper);
}
