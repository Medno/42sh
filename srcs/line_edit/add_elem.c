/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 15:08:37 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/09 16:12:32 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static void	moove_curs(t_line *current, int len, int prompt, t_curs *curseur)
{
	int		i;

	i = -1;
	if (!current->next->next && !curseur->x)
		tputs(tgetstr("do", NULL), 0, &ft_inputchar);
	else
	{
		if (curseur->x && curseur->y < curseur->ymax && current->next->next)
		{
			while (++i <= curseur->x - curseur->xmax)
				tputs(tgetstr("nd", NULL), 0, &ft_inputchar);
			i = curseur->ymax + 1;
			while (--i > curseur->y)
				tputs(tgetstr("up", NULL), 0, &ft_inputchar);
		}
		else if (!curseur->x)
		{
			while (++i < len - 2)
				tputs(tgetstr("le", NULL), 0, &ft_inputchar);
		}
		else
		{
			tputs(tgetstr("rc", NULL), 0, &ft_inputchar);
			tputs(tgetstr("nd", NULL), 0, &ft_inputchar);
		}
	}
}

static void	print_line(t_line *current, int len, int prompt, t_curs *curseur)
{
	t_line	*tmp;
	char	buf[len];
	int		i;

	tmp = current;
	i = 0;
	ft_bzero(buf, len);
	while (tmp->next)
	{
		buf[i] = tmp->c;
		tmp = tmp->next;
		i++;
	}
	tputs(tgetstr("sc", NULL), 0, &ft_inputchar);
	write(STDIN_FILENO, &buf, i);
	check_ynx(curseur, prompt, current->index);
	check_max(curseur, prompt + len + current->index);
	moove_curs(current, len, prompt, curseur);
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
	print_line(new, dblist_len(new), prompt, curseur);
	return (current);
}
