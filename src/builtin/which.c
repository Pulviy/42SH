/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** which
*/

#include "mysh.h"

static int builtin_which_filename(shell_t *shell, char *filename)
{
    char *path = locate_bin(shell, filename);
    int ret = 0;

    if (strchr(filename, '/') || strchr(filename, '.'))
        dprintf(2, "%s: Command not found.\n", filename);
    else if (path)
        dprintf(1, "%s\n", path);
    else {
        dprintf(2, "%s: Command not found.\n", filename);
        ret = 1;
    }
    free(path);
    return (ret);
}

int builtin_which_check_builtins(shell_t *shell, char *file)
{
    int index = 0;

    while (shell->builtin_list[index]) {
        if (!strcmp(shell->builtin_list[index], file)) {
            dprintf(1, "%s: shell built-in command.\n", file);
            return (1);
        }
        index++;
    }
    return (0);
}

int builtin_which_get_first(shell_t *shell)
{
    int tmp = 0;
    int status = 0;
    int i = 1;

    while (shell->cmd_heap->argv[i]) {
        if (!builtin_which_check_builtins(shell, shell->cmd_heap->argv[i]))
            tmp = builtin_which_filename(shell, shell->cmd_heap->argv[i]);
        status = tmp ? tmp : status;
        ++i;
    }
    return (status);
}

int builtin_which(shell_t *shell)
{
    int status = 0;

    if (strcmp(shell->cmd_heap->argv[0], "which"))
        return (0);
    else if (!shell->cmd_heap->argv[1]) {
        dprintf(2, "which: Too few arguments.\n");
        shell->status = 1;
    } else {
        status = builtin_which_get_first(shell);
    }
    shell->status = status;
    return (1);
}
