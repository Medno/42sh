/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 15:08:37 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/27 15:52:18 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

static void	moove_curseur(t_curs *curseur)
{
	if (curseur->y < curseur->ymax)
		UP(curseur->ymax - curseur->y);
	if (curseur->x > curseur->xmax)
	{
		if (!curseur->xmax)
		{
			NL;
			UP(1);
		}
		RIGHT(curseur->x - curseur->xmax);
	}
	else
		LEFT(curseur->xmax - curseur->x);
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
		NL;
	else if (new->next->next)
		moove_curseur(curseur);
}

t_line		*push_new(t_line *current, char c, int prompt, t_curs *curseur)
{
	t_line	*new;

	if (!(new = create_elem(c)))
		return (NULL);
	new->index = current->index;
	increment_all(current, 1);
	new->next = current;
	if (current->prev)
	{
		new->prev = current->prev;
		current->prev->next = new;
	}
	current->prev = new;
	check_ynx(curseur, prompt, new->index);
	check_max(curseur, prompt + full_list_len(new));
	print_line(new, dblist_len(new), curseur);
	return (current);
}
