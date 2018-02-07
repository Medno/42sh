/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 08:57:34 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/07 13:05:21 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static int	read_end(char **line, t_line *elm)
{
	int		i;

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

t_line		*move_left(t_line *cur)
{
	if (cur->prev)
	{
		tputs(tgetstr("le", NULL), 0, ft_inputchar);
		cur = cur->prev;
	}
	return (cur);
}

t_line		*move_right(t_line *cur)
{
	if (cur->next)
	{
		tputs(tgetstr("nd", NULL), 0, ft_inputchar);
		cur = cur->next;
	}
	return (cur);
}

t_line		*ft_line_esc(t_line *cur)
{
	char	buf[8];

	ft_bzero(&buf, 8);
	read(STDIN_FILENO, &buf, 8);
	if (buf[0] == '[')
	{
		if (buf[1] == 'C')
			cur = move_right(cur);
		if (buf[1] == 'D')
			cur = move_left(cur);
	}
	return (cur);
}

t_line	*ft_line_usual(t_line *cur, char c, int len)
{
	cur = push_new(cur, c, len);
	return (cur);
}

int			ft_line_edition(char **line, int prompt_len)
{
	char	c;
	int		ret;
	t_line	*first;
	t_line	*current;

	first = create_elem(0);
	current = first;
	while ((ret = read(STDIN_FILENO, &c, 1)))
	{
		if (c == '\n')
			return (read_end(line, first));
		else if (c == 27)
			current = ft_line_esc(current);
		else
		{
			current = ft_line_usual(current, c, prompt_len);
		}
	}
	return (0);
}
