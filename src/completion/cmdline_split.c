/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** cmdline_split
*/

#include <string.h>

int cmdline_split(char *lineptr, char **beggin, char **pattern)
{
    int i = (lineptr ? (int)strlen(lineptr) : -1);

    for (; lineptr && i >= 0 && !*pattern; --i) {
        if (lineptr[i] == ' ' || lineptr[i] == '\t' || i == 0) {
            *pattern = lineptr + i + (i != 0);
            *beggin = strndup(lineptr, i + (i != 0));
        }
    }
    for (i = 0; *beggin[i]; ++i) {
        if (*beggin[i] != '\t' && *beggin[i] != ' ')
            return (1);
    }
    return (0);
}