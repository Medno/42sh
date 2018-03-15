/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 10:11:51 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/15 09:24:55 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

void	check_screen(t_curs *curseur)
{
	ioctl(STDIN_FILENO, TIOCGWINSZ, &(curseur->screen));
}

void	check_ynx(t_curs *curseur, int index)
{
	check_screen(curseur);
	curseur->y = index / curseur->screen.ws_col;
	curseur->x = index % curseur->screen.ws_col;
}

void	check_max(t_curs *curseur, int len)
{
	check_screen(curseur);
	curseur->xmax = (len - 1) % curseur->screen.ws_col;
	curseur->ymax = (len - 1) / curseur->screen.ws_col;
}

void	init_curs(t_curs *curseur, int prompt)
{
	curseur->x = prompt;
	curseur->y = 0;
	curseur->xmax = prompt;
	curseur->ymax = 0;
}
