/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** is_file_elf
*/

#include <fcntl.h>

#include <unistd.h>

int is_file_elf(char *file)
{
    int fd = file ? open(file, O_RDONLY) : -1;
    char elf[4] = {127, 69, 76, 70};
    char c = 0;
    int check = 1;

    if (fd < 0)
        return (0);
    for (int i = 0; i < 4 && check > 0; ++i) {
        check = read(fd, &c, 1);
        if (c != elf[i])
            check = 0;
    }
    close(fd);
    return (check <= 0 ? 0 : 1);
}