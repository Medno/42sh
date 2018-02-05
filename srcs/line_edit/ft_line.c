#include "21sh.h"

int     ft_line_edition(char **line)
{
    char    c;
    char    buf[8];
    int     ret;

    while ((ret = read(STDIN_FILENO, &c, 1)))
    {
        if (c == '\n')
            return (1);
        else if (c == 27)
        {
            read(STDIN_FILENO, &buf, 8);
            //ft_line_escape();
        }
        else
        {
            //ft_line_norm
            write(0, &c, 1);
        }
        ft_bzero(&buf, 8);
    }
    return (0);
}