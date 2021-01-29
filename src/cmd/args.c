/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** args
*/

#include "mysh.h"

void strn_shift(char *str, int n)
{
    int i = 0;

    if (n <= 0 || !str)
        return;
    while (str && str[i]) {
        str[i] = str[i + n];
        ++i;
    }
}

static int get_argc(char *lineptr)
{
    char *delims = " \t";
    char *begin = lineptr;
    char *end = NULL;
    int inhibitor = 0;
    int quote = 0;

    while (*begin && strchr(delims, *begin))
        ++begin;
    if (!*begin)
        return (0);
    end = begin;
    while (*end && (quote || inhibitor || !strchr(delims, *end))) {
        if (!inhibitor && (*end == '\'' || *end == '\"'))
            quote = (quote == *end ? 0 : (quote == 0 ? *end : quote));
        inhibitor = (!inhibitor && *end == '\\');
        ++end;
    }
    return (1 + get_argc(end));
}

static void get_next_argv(char **lineptr, char **argvptr)
{
    char *delims = " \t";
    char *begin = *lineptr;
    char *end = NULL;
    int inhibitor = 0;
    int quote = 0;

    while (*begin && strchr(delims, *begin))
        ++begin;
    end = begin;
    while (*end && (quote || inhibitor || !strchr(delims, *end))) {
        if (!inhibitor && (*end == '\'' || *end == '\"'))
            quote = (quote == *end ? 0 : (quote == 0 ? *end : quote));
        if (inhibitor)
            strn_shift(end - 1, 1);
        inhibitor = (!inhibitor && *end == '\\');
        ++end;
    }
    begin = (*begin == '\'' || *begin == '\"' ? begin + 1 : begin);
    end -= (*(end - 1) == '\'' || *(end - 1) == '"');
    *argvptr = strndup(begin, end - begin);
    *lineptr = end + (*end == '\'' || *end == '"');
}

void parse_arguments(char *lineptr, char ***argvptr, int *argcptr)
{
    *argcptr = get_argc(lineptr);
    *argvptr = (*argcptr > 0 ? calloc(*argcptr + 1, sizeof(char *)) : NULL);
    int index = 0;

    while (index < *argcptr) {
        get_next_argv(&lineptr, &((*argvptr)[index]));
        ++index;
    }
}