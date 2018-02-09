/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 14:47:01 by pchadeni          #+#    #+#             */
/*   Updated: 2018/02/09 16:13:29 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

t_line		*move_left(t_line *cur, int prompt)
{
	struct winsize	screen;
	int				tot;
	int				i;

	if (cur->prev)
	{
		ioctl(STDIN_FILENO, TIOCGWINSZ, &screen);
		tot = prompt + cur->index;
		i = -1;
		if (!(tot % screen.ws_col))
		{
			tputs(tgetstr("up", NULL), 0, &ft_inputchar);
			while (++i <= screen.ws_col)
				tputs(tgetstr("nd", NULL), 0, &ft_inputchar);
			tputs(tgetstr("le", NULL), 0, &ft_inputchar);
			tputs(tgetstr("nd", NULL), 0, &ft_inputchar);
		}
		else
			tputs(tgetstr("le", NULL), 0, ft_inputchar);
		cur = cur->prev;
	}
	return (cur);
}

t_line		*move_right(t_line *cur, int prompt)
{
	struct winsize	screen;
	int				tot;
	int				i;

	if (cur->next)
	{
		ioctl(STDIN_FILENO, TIOCGWINSZ, &screen);
		tot = prompt + cur->index + 1;
		i = -1;
		if (!(tot % screen.ws_col))
			tputs(tgetstr("do", NULL), 0, &ft_inputchar);
		else
			tputs(tgetstr("nd", NULL), 0, ft_inputchar);
		cur = cur->next;
	}
	return (cur);
}
