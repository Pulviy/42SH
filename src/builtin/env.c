/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** env
*/

#include "mysh.h"
#include <ctype.h>

static int check_setenv(char const *name)
{
    char *msg = NULL;

    if ((*name < 'A' || *name > 'Z') && (*name < 'a' || *name > 'z')) {
        msg = "Variable name must begin with a letter.";
    }
    while (!msg && *name) {
        if (!isalnum(*name) && *name != '_')
            msg = "Variable name must contain alphanumeric characters.";
        ++name;
    }
    if (msg)
        dprintf(2, "setenv: %s\n", msg);
    return (!msg);
}

int builtin_env(shell_t *shell)
{
    if (strcmp(shell->cmd_heap->argv[0], "env"))
        return (0);
    list_print(shell->env_list);
    return (1);
}

int builtin_setenv(shell_t *shell)
{
    instr_t *instr = shell->cmd_heap;

    if (strcmp(instr->argv[0], "setenv"))
        return (0);
    if (instr->argc == 1) {
        list_print(shell->env_list);
    } else if (instr->argc > 3) {
        dprintf(2, "%s: Too many arguments.\n", instr->argv[0]);
        shell->status = 1;
    } else {
        if (check_setenv((char const *)instr->argv[1]))
            my_setenv(shell, instr->argv[1], instr->argv[2]);
        else
            shell->status = 1;
    }
    return (1);
}

int builtin_unsetenv(shell_t *shell)
{
    int index = 1;

    if (strcmp(shell->cmd_heap->argv[0], "unsetenv"))
        return (0);
    if (shell->cmd_heap->argc <= 1) {
        dprintf(2, "%s: Too few arguments.\n", shell->cmd_heap->argv[0]);
        shell->status = 1;
    }
    while (index < shell->cmd_heap->argc) {
        my_unsetenv(shell, shell->cmd_heap->argv[index]);
        ++index;
    }
    return (1);
}