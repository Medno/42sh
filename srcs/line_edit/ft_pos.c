/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 10:11:51 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/10 10:05:20 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	check_ynx(t_curs *curseur, int prompt, int index)
{
	ioctl(STDIN_FILENO, TIOCGWINSZ, &(curseur->screen));
	curseur->y = (prompt + index + 1) / curseur->screen.ws_col;
	curseur->x = (prompt + index + 1) % curseur->screen.ws_col;
}

void	check_max(t_curs *curseur, int len)
{
	ioctl(STDIN_FILENO, TIOCGWINSZ, &(curseur->screen));
	curseur->xmax = (len - 1) % curseur->screen.ws_col;
	curseur->ymax = (len - 2) / curseur->screen.ws_col;
}

void	init_curs(t_curs *curseur, int prompt)
{
	curseur->x = prompt;
	curseur->y = 0;
	curseur->xmax = prompt;
	curseur->ymax = 0;
}
