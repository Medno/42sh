/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 14:47:01 by pchadeni          #+#    #+#             */
/*   Updated: 2018/02/09 16:53:46 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

t_line		*moove_left(t_line *cur, int prompt, t_curs *curseur)
{
	int		i;

	i = -1;
	check_ynx(curseur, prompt, cur->index);
	if (curseur->x == 1 && curseur->y)
	{
		tputs(tgetstr("up", NULL), 0, &ft_inputchar);
		while (++i < curseur->screen.ws_col)
			tputs(tgetstr("nd", NULL), 0, &ft_inputchar);
	}
	else if (cur->prev)
		tputs(tgetstr("le", NULL), 0, &ft_inputchar);
	if (cur->prev)
		cur = cur->prev;
	return (cur);
}

t_line		*moove_right(t_line *cur, int prompt, t_curs *curseur)
{
	int		i;

	i = -1;
	check_ynx(curseur, prompt, cur->index);
	if (cur->next && !curseur->x)
	{
		tputs(tgetstr("do", NULL), 0, &ft_inputchar);
		}
	else if (cur->next)
		tputs(tgetstr("nd", NULL), 0, &ft_inputchar);
	if (cur->next)
		cur = cur->next;
	return (cur);
}
