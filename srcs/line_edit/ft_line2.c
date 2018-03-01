/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 09:12:41 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/28 11:59:51 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

t_line			*paste_line(t_line *cur, char *str, int prompt,
				t_curs *curseur)
{
	while (str && *str)
	{
		cur = push_new(cur, *str, prompt, curseur);
		str++;
	}
	return (cur);
}

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

	if (!count_selected(cur) || count_selected(cur) > 1024)
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

t_line			*ft_line_usual(t_edit *edit, char c)
{
	if (c == 127 || c == 8)
		*(edit->current) = line_delone(*(edit->current), edit->prompt_len, &(edit->curseur));
	else if (c == '\t')// || (c == 4 && !(*(edit->current)->next != NULL)))
		*(edit->current) = completion(*(edit->current), edit->prompt_len, &(edit->curseur));
	else if (c == 4)
		*(edit->current) = del_next(*(edit->current));
	else if (c == 1)
		*(edit->current) = moove_first(*(edit->current), edit->prompt_len, &(edit->curseur));
	else if (c == 2)
		*(edit->current) = moove_left(*(edit->current), edit->prompt_len, &(edit->curseur));
	else if (c == 5)
		*(edit->current) = moove_last(*(edit->current), edit->prompt_len, &(edit->curseur));
	else if (c == 6)
		*(edit->current) = moove_right(*(edit->current), edit->prompt_len, &(edit->curseur));
	else if (c >= 32 && c <= 126)
		*(edit->current) = push_new(*(edit->current), c, edit->prompt_len, &(edit->curseur));
	else
		*(edit->current) = ft_grabb(*(edit->current), c, edit->prompt_len, &(edit->curseur));
	return (*(edit->current));
}
