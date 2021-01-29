/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** where
*/

#include "mysh.h"

static int locate_file(char *dirpath, char *file)
{
    char *dir = strtok(dirpath, ":");
    char *path = NULL;
    int ret = 1;

    while (dir) {
        if (is_in_dir(file, dir)) {
            path = get_bin_path(dir, file);
            dprintf(1, "%s\n", path);
            free(path);
            ret = 0;
        }
        dir = strtok(NULL, ":");
    }
    return (ret);
}

static int builtin_where_filename(shell_t *shell, char *file)
{
    char path[512] = "/bin/";
    int ret = 1;

    if (my_getenv(shell, "PATH") != NULL)
        strncpy(path, my_getenv(shell, "PATH"), 255);
    if (strchr(file, '/'))
        dprintf(2, "where: / in command makes no sense\n");
    else if (strchr(file, '.'))
        return (ret);
    else
        ret = locate_file(path, file);
    return (ret);
}

void builtin_where_check_builtins(shell_t *shell, char *file)
{
    int index = 0;

    while (shell->builtin_list[index]) {
        if (!strcmp(shell->builtin_list[index], file))
            dprintf(1, "%s is a shell built-in\n", file);
        index++;
    }
    return;
}

int builtin_where(shell_t *shell)
{
    int i = 1;
    int tmp = 0;
    int status = 0;

    if (strcmp(shell->cmd_heap->argv[0], "where"))
        return (0);
    else if (!shell->cmd_heap->argv[1]) {
        dprintf(2, "where: Too few arguments.\n");
        shell->status = 1;
    } else {
        while (shell->cmd_heap->argv[i]) {
            builtin_where_check_builtins(shell, shell->cmd_heap->argv[i]);
            tmp = builtin_where_filename(shell, shell->cmd_heap->argv[i]);
            status = tmp ? tmp : status;
            ++i;
        }
    }
    shell->status = status;
    return (1);
}
