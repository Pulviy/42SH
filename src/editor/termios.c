/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** termios
*/

#include <termios.h>
#include <stdlib.h>
#include <unistd.h>

static struct termios *get_termios_origin(void)
{
    static struct termios origin;

    return (&origin);
}

void disable_raw_terminal(void)
{
    struct termios *origin = get_termios_origin();

    tcsetattr(0, TCSAFLUSH, origin);
}

int enable_raw_terminal(void)
{
    struct termios *origin = get_termios_origin();
    struct termios raw;

    if (!isatty(0) || tcgetattr(0, origin) == -1)
        return (0);
    atexit(disable_raw_terminal);
    raw = *origin;
    raw.c_iflag &= ~(BRKINT | INPCK | ICRNL | IXON);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    raw.c_cc[VMIN] = 1;
    raw.c_cc[VTIME] = 0;
    tcsetattr(0, TCSAFLUSH, &raw);
    return (1);
}