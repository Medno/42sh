/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 08:57:34 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/10 11:20:32 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static int	read_end(char **line, t_line *elm)
{
	int		i;

	while (elm->prev)
		elm = elm->prev;
	if (!(*line = (char *)malloc(sizeof(char) * dblist_len(elm) + 1)))
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
	//moove_last();
	write(STDIN_FILENO, "\n", 1);
	return (1);
}

t_line		*ft_line_esc(t_line *cur, int len, t_curs *curseur)
{
	char	buf[8];

	ft_bzero(&buf, 8);
	read(STDIN_FILENO, &buf, 8);
	if (buf[0] == '[')
	{
		if (buf[1] == 'C')
			cur = moove_right(cur, len, curseur);
		if (buf[1] == 'D')
			cur = moove_left(cur, len, curseur);
		if (buf[1] == 'A')
			cur = moove_up(cur, len, curseur);
		if (buf[1] == 'B')
			cur = moove_down(cur, len, curseur);
		if (buf[1] == 'H')
			cur = moove_first(cur, len, curseur);
		if (buf[1] == 'F')
			cur = moove_last(cur, len, curseur);
		if (buf[1] == '3')
			cur = del_next(cur);
	}
	return (cur);
}

t_line		*ft_line_usual(t_line *current, char c, int prompt , t_curs *curseur)
{
	if (c == 127)
		current = line_delone(current, prompt);
	else
		current = push_new(current, c, prompt, curseur);
	return (current);
}

int			ft_line_edition(char **line, int prompt_len)
{
	char			c;
	int				ret;
	t_curs			curseur;
	t_line			*current;

	current = create_elem(0);
	init_curs(&curseur, prompt_len);
	while ((ret = read(STDIN_FILENO, &c, 1)))
	{
		if (c == '\n')
			return (read_end(line, current));
		else if (c == 27)
			current = ft_line_esc(current, prompt_len, &curseur);
		else
			current = ft_line_usual(current, c, prompt_len, &curseur);
	}
	return (0);
}
