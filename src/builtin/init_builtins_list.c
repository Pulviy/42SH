/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** init builtins list
*/

#include "mysh.h"

char **init_builtins_list(void)
{
    char **list = malloc(sizeof(char *) * 15);

    if (!list)
        return (NULL);
    list[0] = strdup("alias");
    list[1] = strdup("cd");
    list[2] = strdup("env");
    list[3] = strdup("setenv");
    list[4] = strdup("unsetenv");
    list[5] = strdup("echo");
    list[6] = strdup("where");
    list[7] = strdup("which");
    list[8] = strdup("repeat");
    list[9] = strdup("exit");
    list[10] = strdup("fg");
    list[11] = strdup("jobs");
    list[12] = strdup("kill");
    list[13] = strdup("bg");
    list[14] = NULL;
    return (list);
}
