/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_grab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 09:10:34 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/02 10:26:52 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

static void		print(t_line *cur, t_curs *curseur)
{
	t_line		*tmp;

	tmp = cur;
	ansi("SAVE", 0, STDIN_FILENO);
	while (tmp->prev)
		tmp = moove_left(tmp, curseur);
	while (tmp)
	{
		if (tmp->select == 1)
			ft_putstr_fd("\033[32m", STDIN_FILENO);
		else if (tmp->select == 2)
			ft_putstr_fd("\033[31;1m", STDIN_FILENO);
		else
			ft_putstr_fd("\033[0m", STDIN_FILENO);
		write(STDIN_FILENO, &tmp->c, 1);
		tmp = tmp->next;
	}
	ansi("REST", 0, STDIN_FILENO);
}

static void		srprint(t_line *cur, t_line *first, t_curs *curseur)
{
	t_line	*tmp;

	tmp = cur;
	while (tmp->prev)
		tmp = tmp->prev;
	while (tmp->next)
	{
		if (cur->index > first->index && tmp->index > first->index
				&& tmp->index <= cur->index)
			tmp->select = 1;
		else if (cur->index < first->index && tmp->index < first->index
				&& tmp->index >= cur->index)
			tmp->select = 1;
		else
			tmp->select = 0;
		tmp = tmp->next;
	}
	first->select = 2;
	print(cur, curseur);
}

static void		underline(t_line *current, int check)
{
	ansi("SAVE", 0, STDIN_FILENO);
	if (current->select == 1)
		ft_putstr_fd("\033[32m", STDIN_FILENO);
	else if (current->select == 2)
		ft_putstr_fd("\033[31;1m", STDIN_FILENO);
	else
		ft_putstr_fd("\033[0m", STDIN_FILENO);
	if (check)
		ft_putstr_fd("\033[4m", STDIN_FILENO);
	if (!current->c)
		write(STDIN_FILENO, " ", 1);
	else
		write(STDIN_FILENO, &current->c, 1);
	ft_putstr_fd("\033[0m", STDIN_FILENO);
	ansi("REST", 0, STDIN_FILENO);
}

static t_line	*escape_mod(t_line *cur, int prompt, t_curs *curseur)
{
	char	buf[8];

	ft_bzero(&buf, 8);
	read(STDIN_FILENO, &buf, 8);
	if (ft_strequ(buf, "[1;2A"))
		cur = moove_up(cur, prompt, curseur);
	else if (ft_strequ(buf, "[1;2B"))
		cur = moove_down(cur, curseur);
	else if (ft_strequ(buf, "[1;2C"))
		cur = moove_rword(cur, curseur);
	else if (ft_strequ(buf, "[1;2D"))
		cur = moove_lword(cur, curseur);
	else if (ft_strequ(buf, "[C"))
		cur = moove_right(cur, curseur);
	else if (ft_strequ(buf, "[D"))
		cur = moove_left(cur, curseur);
	else if (ft_strequ(buf, "[H"))
		cur = moove_first(cur, curseur);
	else if (ft_strequ(buf, "[F"))
		cur = moove_last(cur, curseur);
	return (cur);
}

t_line			*grab_mod(t_line *current, int prompt, t_curs *curseur)
{
	char	c;
	t_line	*tmp;

	tmp = current;
	ansi("CUR_OFF", 0, STDIN_FILENO);
	underline(current, 1);
	while (read(STDIN_FILENO, &c, 1))
	{
		underline(current, 0);
		if (c == 27)
		{
			current = escape_mod(current, prompt, curseur);
			srprint(current, tmp, curseur);
		}
		else if (c == 10)
		{
			ansi("CUR_ON", 0, STDIN_FILENO);
			return (current);
		}
		underline(current, 1);
	}
	return (current);
}
