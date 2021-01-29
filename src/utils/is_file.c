/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** is_file
*/

#include <sys/stat.h>

int is_file(char *path)
{
    struct stat statbuf;

    if (lstat(path, &statbuf) != 0 || S_ISDIR(statbuf.st_mode))
        return (0);
    return (1);
}
