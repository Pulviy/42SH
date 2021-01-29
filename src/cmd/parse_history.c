/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** parse_history
*/

#include "mysh.h"

static int get_hist_id(char *str, int *len)
{
    int index = 0;
    int i = 0;

    *len = 1;
    if (str[*len] == '!') {
        index = -1;
        ++*len;
    } else if (str[*len] == '-')
        ++*len;
    for (i = *len; str[i] >= '0' && str[i] <= '9'; ++i);
    if (index == -1) {
        *len = 1;
        return (-1);
    } else if (i == *len) {
        *len = 0;
        return (0);
    }
    *len = i - 1;
    return (atoi(str + 1));
}

static int get_hist_val(shell_t *shell, char *str, char **value, int *err)
{
    int histsize = list_size((node_t *)shell->history->hist_list);
    int len = 1;
    int index = get_hist_id(str, &len);
    data_node_t *data = NULL;

    *value = "!";
    if (len == 0)
        return (0);
    else if (abs(index) > histsize) {
        *err = 1;
        dprintf(2, "%d: Event not found.\n", index);
        return (0);
    }
    if (index < 0)
        data = list_fetch_id((void **)&shell->history->hist_tail, abs(index));
    else
        data = list_fetch_id((void **)&shell->history->hist_list, index);
    *value = data ? data->data : *value;
    return (len);
}

int parse_history(shell_t *shell, char *lineptr)
{
    int inhibit = 0;
    char save[BUFFSIZE] = {0};
    char *var = NULL;
    int err = 0;

    strcpy(save, lineptr ? lineptr : "\0");
    for (int i = 0; !err && save[i]; ++i) {
        if (save[i] == '\\') {
            inhibit = 1;
            ++lineptr;
        } else if (save[i] == '!' && inhibit <= 0) {
            i += get_hist_val(shell, save + i, &var, &err);
            strcpy(lineptr, var ? var : "\0");
            lineptr += var ? strlen(var) : 0;
        } else {
            *lineptr = save[i];
            ++lineptr;
            --inhibit;
        }
    }
    return (!err);
}