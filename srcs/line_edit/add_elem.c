/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 15:08:37 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/02 10:15:56 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

static void	moove_curseur(t_curs *curseur)
{
	if (curseur->y < curseur->ymax)
		ansi("UP", curseur->ymax - curseur->y, STDIN_FILENO);
	if (curseur->x > curseur->xmax)
	{
		if (!curseur->xmax)
		{
			ansi("NL", 0, STDIN_FILENO);
			ansi("UP", 1, STDIN_FILENO);
		}
		ansi("RI", curseur->x - curseur->xmax, STDIN_FILENO);
	}
	else
		ansi("LE", curseur->xmax - curseur->x, STDIN_FILENO);
}

static void	print_line(t_line *new, int len_end, t_curs *curseur)
{
	char	buf[len_end];
	int		i;
	t_line	*tmp;

	i = 0;
	tmp = new;
	ft_bzero(buf, len_end);
	while (tmp->next)
	{
		buf[i] = tmp->c;
		tmp = tmp->next;
		i++;
	}
	write(STDIN_FILENO, &buf, len_end);
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
	if (c == '\n')
		increment_all(current, curseur->screen.ws_col - curseur->x);
	else
		increment_all(current, 1);
	new->next = current;
	if (current->prev)
	{
		new->prev = current->prev;
		current->prev->next = new;
	}
	current->prev = new;
	check_ynx(curseur, new->index);
	check_max(curseur, last_index(new));
	print_line(new, last_index(new) - new->index, curseur);
	return (current);
}
