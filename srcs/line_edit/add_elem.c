/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 15:08:37 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/11 16:40:16 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

static void	moove_curseur(t_curs *curseur)
{
	if (curseur->y < curseur->ymax && !curseur->xmax)
	{
		ansi("NL", 0, STDIN_FILENO);
		ansi("UP", curseur->ymax - curseur->y, STDIN_FILENO);
		ansi("RI", curseur->x, STDIN_FILENO);
	}
	else if (!curseur->x)
	{
		ansi("REST", 0, STDIN_FILENO);
		ansi("DO", 1, STDIN_FILENO);
		ansi("LE", curseur->screen.ws_col - 1, STDIN_FILENO);
	}
	else
	{
		ansi("REST", 0, STDIN_FILENO);
		ansi("RI", 1, STDIN_FILENO);
	}
}

static void	print_line(t_line *new, int len_end, t_curs *curseur)
{
	char	buf[len_end + 1];
	int		i;
	t_line	*tmp;

	i = 0;
	tmp = new;
	ft_bzero(buf, len_end + 1);
	ansi("SAVE", 0, STDIN_FILENO);
	ansi("CL_END", 0, STDIN_FILENO);
	while (tmp->next)
	{
		buf[i] = tmp->c;
		i++;
		tmp = tmp->next;
	}
	buf[i] = 0;
	if (new->next->next && ft_strchr(buf, '\n') && (new->index + ft_strcspn(buf, "\n")) % curseur->screen.ws_col == 1)
	{
		write(STDIN_FILENO, &buf, ft_strcspn(buf, "\n"));
		write(0, "\n", 1);
		write(STDIN_FILENO, &buf[ft_strcspn(buf, "\n") + 1], i - ft_strcspn(buf, "\n"));
		ansi("REST", 0, STDIN_FILENO);
		ansi("DO", 1, STDIN_FILENO);
		ansi("LE", curseur->screen.ws_col, STDIN_FILENO);
		return ;
	}
	else
		write(STDIN_FILENO, &buf, i);
	if (!new->next->next && !curseur->x)
		ansi("NL", 0, STDIN_FILENO);
	else if (new->next->next)
		moove_curseur(curseur);
}

int			count_len(t_line *cur)
{
	t_line	*tmp;
	int		i;

	tmp = cur;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	increment_all_nl(t_line *cur, t_curs *curseur, int c)
{
	t_line	*tmp;

	tmp = cur;
	while (tmp)
	{
		tmp->index += c;
		if (tmp->c == '\n' && tmp->index % curseur->screen.ws_col != 1)
			break ;
		else if (tmp->c == '\n')
			c = curseur->screen.ws_col;
		tmp = tmp->next;
	}
}

t_line		*push_new(t_line *current, char c, t_curs *curseur)
{
	t_line	*new;

	if (!(new = create_elem(c, current->index)))
		return (NULL);
	new->next = current;
	if (c == '\n')
		increment_all(current, curseur->screen.ws_col - (new->index % curseur->screen.ws_col) + 1);
	else
		increment_all_nl(current, curseur, 1);
	if (current->prev)
	{
		new->prev = current->prev;
		current->prev->next = new;
	}
	current->prev = new;
	check_ynx(curseur, new->index);
	check_max(curseur, last_index(new));
	print_line(new, count_len(current), curseur);
	return (current);
}
