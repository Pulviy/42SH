/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** readline
*/

#include <stdio.h>
#include <sys/types.h>

ssize_t readline(char **buffer, FILE *stream)
{
    size_t n = 0;
    ssize_t readsize = 0;

    readsize = getline(buffer, &n, stream);
    if ((int)readsize < 0)
        return (-1);
    if ((*buffer)[readsize - 1] == '\n')
        (*buffer)[readsize - 1] = '\0';
    return (readsize);
}