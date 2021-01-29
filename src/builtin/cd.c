/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** cd
*/

#include "mysh.h"

static char const *cd_get_special_action(shell_t *shell)
{
    char const *dest = NULL;

    if (strcmp(shell->cmd_heap->argv[1], "-") == 0)
        dest = my_getenv(shell, "OLDPWD");
    else if (strcmp(shell->cmd_heap->argv[1], "~") == 0)
        dest = my_getenv(shell, "HOME");
    return (dest);
}

static char const *cd_get_dest(shell_t *shell)
{
    char const *dest = NULL;

    if (shell->cmd_heap->argc == 1)
        dest = my_getenv(shell, "HOME");
    else if (shell->cmd_heap->argc == 2) {
        dest = cd_get_special_action(shell);
        dest = (!dest ? shell->cmd_heap->argv[1] : dest);
    }
    return (dest);
}

static void update_pwd(shell_t *shell)
{
    char *buf = getcwd(NULL, 0);

    my_setenv(shell, "OLDPWD", my_getenv(shell, "PWD"));
    my_setenv(shell, "PWD", buf);
    free(buf);
}

int builtin_cd(shell_t *shell)
{
    char const *dest = NULL;

    if (strcmp(shell->cmd_heap->argv[0], "cd"))
        return (0);
    dest = cd_get_dest(shell);
    if (dest && chdir(dest) == -1) {
        dprintf(2, "%s: %s.\n", dest, strerror(errno));
        shell->status = 1;
    } else {
        update_pwd(shell);
    }
    return (1);
}