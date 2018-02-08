/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 08:57:34 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/08 15:39:35 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static int	read_end(char **line, t_line *elm)
{
	int		i;

	while (elm->prev)
		elm = elm->prev;
	if (!(*line = (char *)malloc(sizeof(char) * dblist_len(elm))))
		return (0);
	i = 0;
	while (elm)
	{
		(*line)[i] = elm->c;
		elm = elm->next;
		i++;
	}
	(*line)[i] = 0;
	del_elem(elm);
	write(STDIN_FILENO, "\n", 1);
	return (1);
}

t_line		*ft_line_esc(t_line *cur, int len)
{
	char	buf[8];

	ft_bzero(&buf, 8);
	read(STDIN_FILENO, &buf, 8);
	if (buf[0] == '[')
	{
		if (buf[1] == 'C')
			cur = move_right(cur, len);
		if (buf[1] == 'D')
			cur = move_left(cur, len);
		if (buf[1] == '3')
			cur = del_next(cur);
	}
	return (cur);
}

t_line		*ft_line_usual(t_line *cur, char c, int len)
{
	if (c == 127)
		cur = line_delone(cur, len);
	else
		cur = push_new(cur, c, len);
	return (cur);
}

int			ft_line_edition(char **line, int prompt_len)
{
	char	c;
	int		ret;
	t_line	*current;

	current = create_elem(0);
	while ((ret = read(STDIN_FILENO, &c, 1)))
	{
		if (c == '\n')
			return (read_end(line, current));
		else if (c == 27)
			current = ft_line_esc(current, prompt_len);
		else
			current = ft_line_usual(current, c, prompt_len);
	}
	return (0);
}
