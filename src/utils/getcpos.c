/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** getcpos
*/

#include <termios.h>
#include <unistd.h>
#include <stdio.h>

int getcpos(int *xptr, int *yptr)
{
    char buff[16] = {0};
    struct termios save;
    struct termios term;
    int x = 0;
    int y = 0;

    if (!isatty(0) || tcgetattr(0, &save) == -1)
        return (0);
    term = save;
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &term);
    write(1, "\033[6n", 4);
    read(0, buff, 15);
    sscanf(buff, "\033[%d;%dR", &y, &x);
    if (yptr)
        *yptr = y;
    if (xptr)
        *xptr = x;
    tcsetattr(0, TCSANOW, &save);
    return (1);
}