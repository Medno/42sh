#include "21sh.h"

static int read_end(char **line, t_line *elm)
{
    int     i;

    if (!(*line = (char *)malloc(sizeof(char) * dblist_len(elm))))
        return (0);
    i = 0;
    while (elm)
    {
        *line[i] = elm->c;
        elm = elm->next;
        i++;
    }
    *line[i] = 0;
    //free list here;
    write(STDIN_FILENO, "\n", 1);
    return (1);
}

int     ft_line_edition(char **line, int prompt_len)
{
    char    c;
    char    buf[8];
    int     ret;
    t_line  *first;
    t_line  *current;

    current = NULL;
    first = NULL;
    while ((ret = read(STDIN_FILENO, &c, 1)))
    {
        if (c == '\n')
            return (read_end(line, first));
        else if (c == 27)
        {
            ft_bzero(&buf, 8);
            read(STDIN_FILENO, &buf, 8);
            //ft_line_escape();
        }
        else
        {
            //ft_line_norm
            write(0, &c, 1);
        }
    }
    return (0);
}