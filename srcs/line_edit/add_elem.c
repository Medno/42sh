/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 15:08:37 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/08 11:51:35 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static void	print_line(t_line *current, int len, int prompt, char c)
{
	int		x;
	int		tot;
	struct winsize	screen;

	ioctl(STDIN_FILENO, TIOCGWINSZ, &screen);
	tot = prompt + current->index;
	x = tot % screen.ws_col;
	tputs(tgetstr("im", NULL), 0, &ft_inputchar);
	tputs(tgetstr("ic", NULL), 0, &ft_inputchar);
	write(0, &c, 1);
	tputs(tgetstr("ei", NULL), 0, &ft_inputchar);
}

t_line		*push_new(t_line *current, char c, int prompt)
{
	t_line	*new;

	if (!(new = create_elem(c)))
		return (NULL);
	new->index = current->index;
	increment_all(current, 1);
	new->next = current;
	if (current->prev)
	{
		new->prev = current->prev;
		current->prev->next = new;
	}
	current->prev = new;
	print_line(new, dblist_len(new), prompt, c);
	return (current);
}
