/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 14:47:01 by pchadeni          #+#    #+#             */
/*   Updated: 2018/03/02 11:00:33 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

void		ansi(char *str, int x, int fd)
{
	if (ft_strequ(str, "UP"))
		ft_printf_fd(fd, "\033[%dA", x);
	else if (ft_strequ(str, "DO"))
		ft_printf_fd(fd, "\033[%dB", x);
	else if (ft_strequ(str, "LE"))
		ft_printf_fd(fd, "\033[%dD", x);
	else if (ft_strequ(str, "RI"))
		ft_printf_fd(fd, "\033[%dC", x);
	else if (ft_strequ(str, "NL"))
		ft_putstr_fd("\033E", fd);
	else if (ft_strequ(str, "SAVE"))
		ft_putstr_fd("\033[s", fd);
	else if (ft_strequ(str, "REST"))
		ft_putstr_fd("\033[u", fd);
	else if (ft_strequ(str, "CL_END"))
		ft_putstr_fd("\033[J", fd);
	else if (ft_strequ(str, "CUR_OFF"))
		ft_putstr_fd("\033[?25l", fd);
	else if (ft_strequ(str, "CUR_ON"))
		ft_putstr_fd("\033[?25h", fd);
}

t_line		*moove_up(t_line *cur, int prompt, t_curs *curseur)
{
	int		i;

	check_ynx(curseur, cur->index);
	i = curseur->screen.ws_col;
	if (curseur->y)
	{
		if (!(curseur->y - 1))
		{
			if (curseur->x < prompt + 1)
				return (cur);
		}
		ansi("UP", 1, STDIN_FILENO);
		while (--i >= 0 && cur->prev)
			cur = cur->prev;
	}
	return (cur);
}

t_line		*moove_down(t_line *cur, t_curs *curseur)
{
	int		i;

	check_ynx(curseur, cur->index);
	check_max(curseur, last_index(cur));
	i = -1;
	if (curseur->y < curseur->ymax)
	{
		if (curseur->y + 1 == curseur->ymax && curseur->x > curseur->xmax + 1)
			return (cur);
		ansi("DO", 1, STDIN_FILENO);
		while (++i < curseur->screen.ws_col)
			cur = cur->next;
	}
	return (cur);
}

t_line		*moove_left(t_line *cur, t_curs *curseur)
{
	check_ynx(curseur, cur->index);
	if (cur->prev)
	{
		if (cur->prev->c == '\n')
		{
			ansi("UP", 1, STDIN_FILENO);
			ansi("RI", curseur->screen.ws_col - (cur->index - cur->prev->index), STDIN_FILENO);
		}
		else if (curseur->x == 1 && curseur->y)
		{
			ansi("UP", 1, STDIN_FILENO);
			ansi("RI", curseur->screen.ws_col - 1, STDIN_FILENO);
		}
		else
			ansi("LE", 1, STDIN_FILENO);
		cur = cur->prev;
	}
	return (cur);
}

t_line		*moove_right(t_line *cur, t_curs *curseur)
{
	check_ynx(curseur, cur->index);
	if (cur->next)
	{
		if (!curseur->x || cur->c == '\n')
			ansi("NL", 0, STDIN_FILENO);
		else
			ansi("RI", 1, STDIN_FILENO);
		cur = cur->next;
	}
	return (cur);
}
