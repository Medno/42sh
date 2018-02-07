/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chain_db.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 08:56:09 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/07 15:04:45 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

t_line	*create_elem(char c)
{
	t_line	*new;

	if (!(new = (t_line *)malloc(sizeof(t_line))))
		return (NULL);
	new->c = c;
	new->index = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

int		dblist_len(t_line *first)
{
	int		i;
	t_line	*tmp;

	i = 0;
	tmp = first;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void	increment_all(t_line *current, char c)
{
	t_line	*tmp;

	tmp = current;
	while (tmp)
	{
		tmp->index += c;
		tmp = tmp->next;
	}
}

void	print_line(t_line *current, int len, int prompt)
{
	t_line	*tmp;
	char	buf[len];
	int		i;

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
	tputs(tgetstr("nd", NULL), 0, &ft_inputchar);
}

t_line	*push_new(t_line *current, char c, int prompt)
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
