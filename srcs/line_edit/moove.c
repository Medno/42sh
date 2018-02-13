/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 14:47:01 by pchadeni          #+#    #+#             */
/*   Updated: 2018/02/10 11:12:31 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

t_line		*moove_up(t_line *cur, int prompt, t_curs *curseur)
{
	int		i;

	check_ynx(curseur, prompt, cur->index);
	i = curseur->screen.ws_col;
	if (curseur->y)
	{
		if (!(curseur->y - 1))
		{
			if (curseur->x < prompt + 1)
				return (cur);
		}
		tputs(tgetstr("up", NULL), 0, &ft_inputchar);
		while (--i >= 0)
			cur = cur->prev;
	}
	return (cur);
}

t_line		*moove_down(t_line *cur, int prompt, t_curs *curseur)
{
	int		i;

	check_ynx(curseur, prompt, cur->index);
	check_max(curseur, prompt + full_list_len(cur));
	i = -1;
	if (curseur->y < curseur->ymax)
	{
		if (curseur->y + 1 == curseur->ymax && curseur->x > curseur->xmax + 1)
			return (cur);
		tputs(tgetstr("sf", NULL), 0, &ft_inputchar);
		while (++i < curseur->x - 1)
			tputs(tgetstr("nd", NULL), 0, &ft_inputchar);
		i = -1;
		while (++i < curseur->screen.ws_col)
			cur = cur->next;
	}
	return (cur);
}

t_line		*moove_left(t_line *cur, int prompt, t_curs *curseur)
{
	int		i;

	i = -1;
	check_ynx(curseur, prompt, cur->index);
	if (cur->prev)
	{
		if (curseur->x == 1 && curseur->y)
		{
			tputs(tgetstr("up", NULL), 0, &ft_inputchar);
			while (++i < curseur->screen.ws_col)
				tputs(tgetstr("nd", NULL), 0, &ft_inputchar);
		}
		else
			tputs(tgetstr("le", NULL), 0, &ft_inputchar);
		cur = cur->prev;
	}
	return (cur);
}

t_line		*moove_right(t_line *cur, int prompt, t_curs *curseur)
{
	check_ynx(curseur, prompt, cur->index);
	if (cur->next)
	{
		if (!curseur->x)
			tputs(tgetstr("sf", NULL), 0, &ft_inputchar);
		else
			tputs(tgetstr("nd", NULL), 0, &ft_inputchar);
		cur = cur->next;
	}
	return (cur);
}
