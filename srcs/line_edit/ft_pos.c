/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 10:11:51 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/14 12:17:50 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

void	check_ynx(t_curs *curseur, int index)
{
	ioctl(STDIN_FILENO, TIOCGWINSZ, &(curseur->screen));
	curseur->y = index / curseur->screen.ws_col;
	curseur->x = index % curseur->screen.ws_col;
}

void	check_ynx_nl(t_curs *curseur, t_line *cur)
{
	t_line	*tmp;

	tmp = cur;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &(curseur->screen));
	curseur->y = cur->index / curseur->screen.ws_col;
	curseur->x = cur->index % curseur->screen.ws_col;
	curseur->nl = 0;
	while (tmp)
	{
		if (tmp->c == '\n' && tmp->index % curseur->screen.ws_col == 1 &&
				tmp->prev && tmp->prev->c != '\n')
			curseur->nl = 1;
		tmp = tmp->next;
	}
}

void	check_max(t_curs *curseur, int len)
{
	ioctl(STDIN_FILENO, TIOCGWINSZ, &(curseur->screen));
	curseur->xmax = (len - 1) % curseur->screen.ws_col;
	curseur->ymax = (len - 1) / curseur->screen.ws_col;
}

void	init_curs(t_curs *curseur, int prompt)
{
	curseur->x = prompt;
	curseur->y = 0;
	curseur->nl = 0;
	curseur->xmax = prompt;
	curseur->ymax = 0;
}
