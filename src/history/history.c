/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** history
*/

#include "mysh.h"

history_t *history_new(void)
{
    char const *histfile = HIST_LOC;
    history_t *history = malloc(sizeof(history_t));

    if (!history)
        return (NULL);
    history->hist_tail = NULL;
    history->hist_list = read_history(history, histfile);
    history->histfd = open(histfile, O_WRONLY | O_APPEND);
    return (history);
}

void history_destroy(history_t *history)
{
    if (history->histfd != -1)
        close(history->histfd);
    if (history->hist_list)
        list_destroy((void **)&history->hist_list);
}