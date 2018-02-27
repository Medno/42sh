/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 09:12:41 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/26 14:21:58 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static int		count_selected(t_line *cur)
{
	t_line	*tmp;
	int		i;

	tmp = cur;
	i = 0;
	while (tmp->prev)
		tmp = tmp->prev;
	while (tmp)
	{
		if (tmp->select)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

static char		*foo_paste(t_line *cur)
{
	t_line		*tmp;
	static char	str[1024];
	int			i;

	if (!count_selected(cur))
		return ((char *)&str[0]);
	ft_bzero(str, 1024);
	tmp = cur;
	while (tmp->prev)
		tmp = tmp->prev;
	i = 0;
	while (tmp)
	{
		if (tmp->select)
		{
			str[i] = tmp->c;
			i++;
		}
		tmp = tmp->next;
	}
	str[i] = 0;
	return ((char *)&str[0]);
}

static t_line	*ft_grabb(t_line *cur, char c, int prompt, t_curs *curseur)
{
	static char	*str;
	char		*tmp;

	if (c == 7)
	{
		cur = grab_mod(cur, prompt, curseur);
		str = foo_paste(cur);
		ft_printf_fd(STDIN_FILENO, "\033[s");
		moove_first(cur, prompt, curseur);
		ft_printf_fd(STDIN_FILENO, "\033[J");
		tmp = line_to_str(cur);
		write(0, tmp, ft_strlen(tmp));
		ft_printf_fd(STDIN_FILENO, "\033[u");
	}
	else if (c == 11)
		cur = paste_line(cur, str, prompt, curseur);
	return (cur);
}

t_line			*ft_line_usual(t_line *current, char c, int prompt,
				t_curs *curseur)
{
	if (c == 127 || c == 8)
		current = line_delone(current, prompt, curseur);
	else if (c == '\t' || (c == 4 && !current->next))
		current = completion(current, prompt, curseur);
	else if (c == 4)
		current = del_next(current);
	else if (c == 1)
		current = moove_first(current, prompt, curseur);
	else if (c == 2)
		current = moove_left(current, prompt, curseur);
	else if (c == 5)
		current = moove_last(current, prompt, curseur);
	else if (c == 6)
		current = moove_right(current, prompt, curseur);
	else if (c >= 32 && c <= 126)
		current = push_new(current, c, prompt, curseur);
	else
		current = ft_grabb(current, c, prompt, curseur);
	return (current);
}
