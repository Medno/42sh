/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 10:11:51 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/09 18:19:00 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	check_ynx(t_curs *curseur, int prompt, int index)
{
	ioctl(STDIN_FILENO, TIOCGWINSZ, &(curseur->screen));
	curseur->x = (prompt + index) % (curseur->screen.ws_col - 1);
	curseur->y = (prompt + index) / (curseur->screen.ws_col - 1);
}

void	check_max(t_curs *curseur, int len)
{
	ioctl(STDIN_FILENO, TIOCGWINSZ, &(curseur->screen));
	curseur->xmax = len % (curseur->screen.ws_col - 1);
	curseur->ymax = (len - 2) / (curseur->screen.ws_col);
}

void	init_curs(t_curs *curseur, int prompt)
{
	curseur->x = prompt;
	curseur->y = 0;
	curseur->xmax = prompt;
	curseur->ymax = 0;
}
