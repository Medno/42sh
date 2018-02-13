/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pasting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 09:10:34 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/13 15:38:47 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static void		print(t_line *cur, int prompt, t_curs *curseur)
{
	t_line		*tmp;

	tmp = cur;
	tputs(tgetstr("sc", NULL), 0, &ft_inputchar);
	while (tmp->prev)
		tmp = moove_left(tmp, prompt, curseur);
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
	tputs(tgetstr("rc", NULL), 0, &ft_inputchar);
}

static void		srprint(t_line *cur, t_line *first, int prompt, t_curs *curseur)
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
	print(cur, prompt, curseur);
}

static void		underline(t_line *current, int check)
{
	tputs(tgetstr("sc", NULL), 0, &ft_inputchar);
	if (current->select == 1)
		ft_putstr_fd("\033[32m", STDIN_FILENO);
	else if (current->select == 2)
		ft_putstr_fd("\033[31;1m", STDIN_FILENO);
	else
		ft_putstr_fd("\033[0m", STDIN_FILENO);
	if (check)
		tputs(tgetstr("us", NULL), 0, &ft_inputchar);
	if (!current->c)
		write(STDIN_FILENO, " ", 1);
	else
		write(STDIN_FILENO, &current->c, 1);
	tputs(tgetstr("me", NULL), 0, &ft_inputchar);
	tputs(tgetstr("rc", NULL), 0, &ft_inputchar);
}

static t_line	*escape_mod(t_line *cur, int prompt, t_curs *curseur)
{
	char	buf[8];

	ft_bzero(&buf, 8);
	read(STDIN_FILENO, &buf, 8);
	if (ft_strequ(buf, "[1;2A"))
		cur = moove_up(cur, prompt, curseur);
	else if (ft_strequ(buf, "[1;2B"))
		cur = moove_down(cur, prompt, curseur);
	else if (ft_strequ(buf, "[1;2C"))
		cur = moove_rword(cur, prompt, curseur);
	else if (ft_strequ(buf, "[1;2D"))
		cur = moove_lword(cur, prompt, curseur);
	else if (ft_strequ(buf, "[C"))
		cur = moove_right(cur, prompt, curseur);
	else if (ft_strequ(buf, "[D"))
		cur = moove_left(cur, prompt, curseur);
	else if (ft_strequ(buf, "[H"))
		cur = moove_first(cur, prompt, curseur);
	else if (ft_strequ(buf, "[F"))
		cur = moove_last(cur, prompt, curseur);
	return (cur);
}

t_line			*grab_mod(t_line *current, int prompt, t_curs *curseur)
{
	char	c;
	t_line	*tmp;

	tmp = current;
	tputs(tgetstr("vi", NULL), 0, &ft_inputchar);
	underline(current, 1);
	while (read(STDIN_FILENO, &c, 1))
	{
		underline(current, 0);
		if (c == 27)
		{
			current = escape_mod(current, prompt, curseur);
			srprint(current, tmp, prompt, curseur);
		}
		else if (c == 10)
		{
			tputs(tgetstr("ve", NULL), 0, &ft_inputchar);
			return (current);
		}
		underline(current, 1);
	}
	return (current);
}
