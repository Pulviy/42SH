/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** envvars_replace
*/

#include "mysh.h"

char *my_getlocals(shell_t *shell, char const *name)
{
    data_node_t *buffer = NULL;
    size_t len = (name ? strlen(name) : 0);

    if (!name)
        return (NULL);
    while (list_poll(shell->locals, (void **)&buffer)) {
        if (!strncmp(buffer->data, name, len) && buffer->data[len] == '=')
            return (&buffer->data[len + 1]);
    }
    return (NULL);
}

static int get_var_val(shell_t *shell, char *str, char **value)
{
    int i = 0;
    int check = 0;
    char *name = NULL;

    if (str[0] == '$')
        ++str;
    while (str[i] && str[i] != '\\' && !check) {
        if ((str[i] >= 48 && str[i] <= 57) || (str[i] >= 65 && str[i] <= 90))
            ++i;
        else if ((str[i] >= 97 && str[i] <= 122) || str[i] == 95)
            ++i;
        else
            check = 1;
    }
    name = strndup(str, i - (str[i] == '\\'));
    *value = my_getenv(shell, name);
    *value = *value ? *value : my_getlocals(shell, name);
    i = name ? strlen(name) : 0;
    free(name);
    return (i);
}

void parse_envvar(shell_t *shell, char *lineptr)
{
    int inhibit = 0;
    char save[BUFFSIZE] = {0};
    char *var = NULL;
    int namelen = 0;

    strcpy(save, lineptr ? lineptr : "\0");
    for (int i = 0; save[i]; ++i) {
        if (save[i] == '\\') {
            inhibit = 1;
            ++lineptr;
        } else if (save[i] == '$' && save[i + 1] && inhibit <= 0) {
            namelen = get_var_val(shell, save + i, &var);
            strcpy(lineptr, var ? var : "\0");
            i += namelen;
            lineptr += var ? strlen(var) : 0;
        } else {
            *lineptr = save[i];
            ++lineptr;
            --inhibit;
        }
    }
}