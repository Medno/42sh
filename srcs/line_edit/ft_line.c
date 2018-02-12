/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 08:57:34 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/12 13:42:52 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static int	read_end(char **line, t_line *elm, int prompt, t_curs *curseur)
{
	int		i;

	if (!(*line = (char *)malloc(sizeof(char) * full_list_len(elm) + 1)))
		return (0);
	i = 0;
	elm = moove_first(elm, prompt, curseur);
	while (elm->next)
	{
		(*line)[i] = elm->c;
		elm = moove_right(elm, prompt, curseur);
		i++;
	}
	(*line)[i] = 0;
	del_elem(elm);
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

t_line		*ft_line_esc(t_line *cur, int len, t_curs *curseur, t_hist *histo)
{
	char	buf[8];

	ft_bzero(&buf, 8);
	read(STDIN_FILENO, &buf, 8);
	if (ft_strequ(buf, "[A"))
		;
	else if (ft_strequ(buf, "[B"))
		(void)histo;
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

t_line		*ft_line_usual(t_line *current, char c, int prompt, t_curs *curseur)
{
	if (c == 127)
		current = line_delone(current, prompt, curseur);
	else if (c == '\t')
		current = completion(current, prompt, curseur);
	else
		current = push_new(current, c, prompt, curseur);
	return (current);
}

int			ft_line_edition(char **line, int prompt_len, t_hist *histo)
{
	char			c;
	int				ret;
	t_curs			curseur;
	t_line			*current;

	current = create_elem(0);
	init_curs(&curseur, prompt_len);
	while ((ret = read(STDIN_FILENO, &c, 1)))
	{
		if (c == '\n')
			return (read_end(line, current, prompt_len, &curseur));
		else if (c == 27)
			current = ft_line_esc(current, prompt_len, &curseur, histo);
		else
			current = ft_line_usual(current, c, prompt_len, &curseur);
	}
	return (0);
}
