/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 15:08:37 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/08 17:15:29 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static void	moove_curs(t_line *current, int len, int prompt, int i)
{
	int		tot;
	struct winsize	screen;

	ioctl(STDIN_FILENO, TIOCGWINSZ, &screen);
	tot = prompt + current->index;
	if (!(current->next->next) && !((tot + 1) % screen.ws_col))
		tputs(tgetstr("do", NULL), 0, &ft_inputchar);
	else if (current->next->next && !((tot + len) % screen.ws_col))
	{
		i--;
		while (--i)
			tputs(tgetstr("le", NULL), 0, &ft_inputchar);
	}
	else
		while (--i)
			tputs(tgetstr("le", NULL), 0, &ft_inputchar);
}

static void	print_line(t_line *current, int len, int prompt)
{
	t_line	*tmp;
	char	buf[len];
	int		i;

	tmp = current;
	i = 0;
	ft_bzero(buf, len);
	while (tmp->next)
	{
		buf[i] = tmp->c;
		tmp = tmp->next;
		i++;
	}
	write(STDIN_FILENO, &buf, i);
	moove_curs(current, len, prompt, i);
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
