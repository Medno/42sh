/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tline2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 11:29:54 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/18 11:22:30 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

t_line	*push_noprint(t_line *current, char c, t_curs *curseur)
{
	t_line	*new;

	if (!(new = create_elem(c, current->index)))
		return (NULL);
	new->next = current;
	if (c == '\n')
		increment_all(current, curseur, curseur->screen.ws_col -
				(new->index % curseur->screen.ws_col) + 1);
	else
		increment_all(current, curseur, 1);
	if (current->prev)
	{
		new->prev = current->prev;
		current->prev->next = new;
	}
	current->prev = new;
	check_ynx(curseur, new->index);
	check_max(curseur, last_index(new));
	return (current);
}

t_line	*str_to_line(char *str, int prompt, t_curs *curseur)
{
	t_line	*cur;

	cur = create_elem(0, prompt + 1);
	while (str && *str && *(str + 1))
	{
		cur = push_noprint(cur, *str, curseur);
		str++;
	}
	while (cur->next)
		cur = cur->next;
	return (cur);
}

char	*line_to_str(t_line *cur)
{
	char	*str;
	int		i;

	if (!cur->prev && !cur->next && !cur->c)
		return (NULL);
	if (!(str = malloc(sizeof(char) * full_tline_len(cur) + 1)))
		return (NULL);
	i = 0;
	while (cur->prev)
		cur = cur->prev;
	while (cur->next)
	{
		str[i] = cur->c;
		cur = cur->next;
		i++;
	}
	str[i] = 0;
	return (str);
}

void	increment_all(t_line *current, t_curs *curseur, int c)
{
	t_line	*tmp;

	tmp = current;
	while (tmp)
	{
		tmp->index += c;
		if (tmp->c == '\n' && tmp->index % curseur->screen.ws_col != 1)
			break ;
		else if (tmp->c == '\n')
			c = curseur->screen.ws_col;
		tmp = tmp->next;
	}
}

int		parted_tline_len(t_line *cur)
{
	int		i;

	i = 0;
	while (cur)
	{
		i++;
		cur = cur->next;
	}
	return (i);
}
