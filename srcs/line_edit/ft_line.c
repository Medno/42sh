/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 08:57:34 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/07 12:14:57 by pchadeni         ###   ########.fr       */
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

void		move_left(t_line *cur, int *index)
{
	if (cur->prev)
		tputs(tgetstr("nd", NULL), 0, ft_inputchar);
}

void		move_right(t_line *cur, int *index)
{
	if (cur->next)
		tputs(tgetstr("le", NULL), 0, ft_inputchar);
}

void		ft_line_esc(t_line *cur, int *index)
{
	char	buf[8];

	ft_bzero(&buf, 8);
	read(STDIN_FILENO, &buf, 8);
	if (buf[0] == '[')
	{
		if (buf[1] == 'C')
			move_left(cur, index);
		if (buf[1] == 'D')
			move_right(cur, index);
	}
}

void		ft_line_usual(t_line *cur)
{
	
}

int			ft_line_edition(char **line, int prompt_len)
{
	char	c;
	int		ret;
	t_line	*first;
	t_line	*current;

	first = create_elem(-1);
	current = first;
	while ((ret = read(STDIN_FILENO, &c, 1)))
	{
		if (c == '\n')
			return (read_end(line, first));
		else if (c == 27)
			ft_line_esc(current, buf, &ret);
		else
		{
			//ft_line_norm
			write(0, &c, 1);
		}
	}
	return (0);
}
