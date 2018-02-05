#include "21sh.h"

t_line  *create_elem(char c)
{
    t_line  *new;

    if (!(new = malloc(sizeof(t_line))))
        return (NULL);
    new->c = c;
    new->index = 0;
    new->next = NULL;
    new->prev = NULL;
    return (new);
}

int     dblist_len(t_line *first)
{
    int     i;

    i = 0;
    while (first)
    {
        first = first->next;
        i++;
    }
    return (i);
}

void    add_elem(t_line **line, char c)
{
    t_line  *new;

    new = create_elem(c);
    if (!*line)
        *line = new;
    else
    {

    }

}