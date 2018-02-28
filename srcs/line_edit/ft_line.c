/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 08:57:34 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/28 15:18:57 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

static int	read_end(char **line, t_line *elm, t_hist **histo)
{
	handle_history_ret(elm, histo);
	*line = line_to_str(elm);
	free_dblist(elm);
	write(STDIN_FILENO, "\n", 1);
	return (1);
}

t_line		*ft_line_esc_2(t_line *cur, int prompt, t_curs *curseur, char *buf)
{
	if (ft_strequ(buf, "[1;2A"))
		cur = moove_up(cur, prompt, curseur);
	else if (ft_strequ(buf, "[1;2B"))
		cur = moove_down(cur, prompt, curseur);
	else if (ft_strequ(buf, "[1;2C"))
		cur = moove_rword(cur, prompt, curseur);
	else if (ft_strequ(buf, "[1;2D"))
		cur = moove_lword(cur, prompt, curseur);
	return (cur);
}

t_line		*ft_line_esc(t_line *cur, int len, t_curs *curseur, t_hist **histo)
{
	char	buf[8];

	ft_bzero(&buf, 8);
	read(STDIN_FILENO, &buf, 8);
	if (ft_strequ(buf, "[A"))
		cur = hist_up(cur, histo, len, curseur);
	else if (ft_strequ(buf, "[B"))
		cur = hist_down(cur, histo, len, curseur);
	else if (ft_strequ(buf, "[C"))
		cur = moove_right(cur, len, curseur);
	else if (ft_strequ(buf, "[D"))
		cur = moove_left(cur, len, curseur);
	else if (ft_strequ(buf, "[H"))
		cur = moove_first(cur, len, curseur);
	else if (ft_strequ(buf, "[F"))
		cur = moove_last(cur, len, curseur);
	else if (ft_strequ(buf, "[3~"))
		cur = del_next(cur);
	else
		cur = ft_line_esc_2(cur, len, curseur, buf);
	return (cur);
}

static void	moove_curseur(t_curs *curseur)
{
	if (curseur->y < curseur->ymax)
		UP(curseur->ymax - curseur->y);
	if (curseur->x > curseur->xmax)
	{
		if (!curseur->xmax)
		{
			NL;
			UP(1);
		}
		RIGHT(curseur->x - curseur->xmax);
	}
	else
		LEFT(curseur->xmax - curseur->x);
}

static void	print_line(t_line *new, int len_end, t_curs *curseur)
{
	char	buf[len_end];
	int		i;
	t_line	*tmp;

	i = 0;
	tmp = new;
	ft_bzero(buf, len_end);
	while (tmp->next)
	{
		buf[i] = tmp->c;
		tmp = tmp->next;
		i++;
	}
	write(STDIN_FILENO, &buf, len_end);
	if (!new->next->next && !curseur->x)
		NL;
	else if (new->next->next)
		moove_curseur(curseur);
}

int			read_line(char **line, t_line **current, int prompt_len,
			t_hist **histo)
{
	char	c;
	t_curs	curseur;

	if (prompt_len == -1)
	{
		prompt_len = 2;
		ft_printf("{tred}> {eoc}");
	}
	init_curs(&curseur, prompt_len);
	while (read(STDIN_FILENO, &c, 1))
	{
		if (c == 4 && !(*current)->next && !(*current)->prev)
			return (0);//HANDLE_CTRLD_exit
		else if (c == '\n')
		{
			(*current) = moove_last((*current), prompt_len, &curseur);
			return (read_end(line, (*current), histo));
		}
		else if (c == 14)
			(*current) = hist_down((*current), histo, prompt_len, &curseur);
		else if (c == 16)
			(*current) = hist_up((*current), histo, prompt_len, &curseur);
		else if (c == 27)
			(*current) = ft_line_esc((*current), prompt_len, &curseur, histo);
		else if (c == 9)
		{
			t_line *tmp = *current; while (tmp) {ft_printf("[%c][%d][%d]", tmp->c, tmp->index, tmp->select); tmp = tmp->next;}
			print_line(*current, dblist_len(*current), &curseur);
		}
		else
			(*current) = ft_line_usual((*current), c, prompt_len, &curseur);
	}
	return (0);
}

int			ft_line_edition(char **line, int prompt_len, t_hist **histo)
{
	t_line			*current;

	current = create_elem(0);
	init_hist(histo);
	if (read_line(line, &current, prompt_len, histo))
		return (1);
	return (0);
}
