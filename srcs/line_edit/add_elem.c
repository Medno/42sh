/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 15:08:37 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/15 09:14:51 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

static void	moove_curseur(t_curs *curseur)
{
	if (!curseur->xmax)
	{
		ansi("NL", 0, STDIN_FILENO);
		ansi("UP", curseur->ymax - curseur->y, STDIN_FILENO);
		ansi("RI", curseur->x, STDIN_FILENO);
	}
	else if (!curseur->x)
	{
		ansi("LE", curseur->xmax, STDIN_FILENO);
		if (curseur->ymax != curseur->y)
			ansi("UP", curseur->ymax - curseur->y, STDIN_FILENO);
	}
	else
	{
		if (curseur->ymax != curseur->y)
			ansi("UP", curseur->ymax - curseur->y, STDIN_FILENO);
		ansi("LE", curseur->xmax, STDIN_FILENO);
		ansi("RI", curseur->x, STDIN_FILENO);
	}
}

static void	print_line(t_line *new, int len_end, t_curs *curseur)
{
	char	buf[len_end + 1];
	int		i;
	t_line	*tmp;

	i = 0;
	tmp = new;
	ft_bzero(buf, len_end + 1);
	ansi("CL_END", 0, STDIN_FILENO);
	while (tmp->next)
	{
		buf[i] = tmp->c;
		if (tmp->c == '\n' && tmp->prev && tmp->index % curseur->screen.ws_col
				== 1 && tmp->prev->c != '\n')
		{
			buf[i] = '\n';
			buf[++i] = '\n';
		}
		i++;
		tmp = tmp->next;
	}
	write(STDIN_FILENO, &buf, i);
	if (!new->next->next && !curseur->x)
		ansi("NL", 0, STDIN_FILENO);
	else if (new->next->next)
		moove_curseur(curseur);
}

t_line		*push_new(t_line *current, char c, t_curs *curseur)
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
	print_line(new, parted_tline_len(current), curseur);
	return (current);
}
