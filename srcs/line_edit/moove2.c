/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 11:13:34 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/10 11:27:23 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

t_line		*moove_first(t_line *cur, int prompt, t_curs *curseur)
{
	int		i;

	check_ynx(curseur, prompt, cur->index);
	if (curseur->x < prompt + 1)
	{
		i = curseur->x;
		while (++i <= prompt + 1)
			tputs(tgetstr("nd", NULL), 0, &ft_inputchar);
	}
	else if (curseur->x > prompt + 1)
	{
		i = curseur->x;
		while (--i >= prompt + 1)
			tputs(tgetstr("le", NULL), 0, &ft_inputchar);
	}
	if (curseur->y)
	{
		i = curseur->y + 1;
		while (--i)
			tputs(tgetstr("up", NULL), 0, &ft_inputchar);
	}
	while (cur->prev)
		cur = cur->prev;
	return (cur);
}

t_line		*moove_last(t_line *cur, int prompt, t_curs *curseur)
{
	int		i;

	check_ynx(curseur, prompt, cur->index);
	check_max(curseur, prompt + full_list_len(cur));
	i = curseur->x - 1;
	while (cur->next)
		cur = cur->next;
	if (curseur->y < curseur->ymax)
	{
		i = curseur->y;
		while (++i <= curseur->ymax)
			tputs(tgetstr("sf", NULL), 0, &ft_inputchar);
		i = 0;
	}
	while (++i <= curseur->xmax)
		tputs(tgetstr("nd", NULL), 0, &ft_inputchar);
	return (cur);
}
