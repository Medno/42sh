/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 15:08:37 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/12 13:17:01 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static void	moove_curseur(t_curs *curseur)
{
	int		i;

	if (curseur->y < curseur->ymax)
	{
		i = curseur->y;
		while (++i <= curseur->ymax)
			tputs(tgetstr("up", NULL), 0, &ft_inputchar);
	}
	if (curseur->x > curseur->xmax)
	{
		if (!curseur->xmax)
		{
			tputs(tgetstr("sf", NULL), 0, &ft_inputchar);
			tputs(tgetstr("up", NULL), 0, &ft_inputchar);
		}
		i = curseur->xmax;
		while (++i <= curseur->x)
			tputs(tgetstr("nd", NULL), 0, &ft_inputchar);
	}
	else
	{
		i = curseur->x;
		while (++i <= curseur->xmax)
			tputs(tgetstr("le", NULL), 0, &ft_inputchar);
	}
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
		tputs(tgetstr("sf", NULL), 0, &ft_inputchar);
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
