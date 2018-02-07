/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 15:08:37 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/07 17:28:47 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static void	step_2(t_line *current, int len, int prompt)
{
	int		x;
	int		y;
	int		tot;
	struct winsize	screen;

	ioctl(STDIN_FILENO, TIOCGWINSZ, &screen);
	tot = prompt + current->index + 1;
	x = tot % screen.ws_col;
	if (!x)
		tputs(tgetstr("do", NULL), 0, &ft_inputchar);
	else
		tputs(tgetstr("nd", NULL), 0, &ft_inputchar);
}

static void	print_line(t_line *current, int len, int prompt)
{
	t_line			*tmp;
	char			buf[len];
	int				i;

	ft_bzero(buf, len);
	i = 0;
	tmp = current;
	while (tmp)
	{
		buf[i] = tmp->c;
		tmp = tmp->next;
		i++;
	}
	tputs(tgetstr("sc", NULL), 0, &ft_inputchar);
	write(STDIN_FILENO, &buf, len);
	tputs(tgetstr("rc", NULL), 0, &ft_inputchar);
	step_2(current, len, prompt);
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
	print_line(new, dblist_len(new), prompt);
	return (current);
}
