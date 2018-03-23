/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookup_historic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 10:05:33 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/23 15:11:19 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

static char	reset(t_edit *edit, char c)
{
	char	*tmp;

	if (c != 3)
	{
		*edit->current = move_first(*edit->current, &edit->curseur);
		ansi("LE", (&edit->curseur)->screen.ws_col, STDIN_FILENO);
		ansi("CL_END", 0, STDIN_FILENO);
		edit->prompt_len = put_path(&edit->env);
		tmp = line_to_str(*edit->current);
		ft_putstr_fd(tmp, STDIN_FILENO);
		ansi("REST", 0, STDIN_FILENO);
		ft_strdel(&tmp);
		*edit->current = move_last(*edit->current, &edit->curseur);
	}
	return (c);
}

static void	init_lookup(t_edit *edit)
{
	char	*tmp;

	*edit->current = move_first(*edit->current, &edit->curseur);
	ansi("SAVE", 0, STDIN_FILENO);
	ansi("LE", edit->prompt_len + 1, STDIN_FILENO);
	ansi("CL_END", 0, STDIN_FILENO);
	edit->prompt_len = ft_printf_fd(STDIN_FILENO, "(reverse-i-search): ");
	tmp = line_to_str(*edit->current);
	ft_putstr_fd(tmp, STDIN_FILENO);
	ft_strdel(&tmp);
}

static t_line *clear(t_edit *edit, char *buf)
{
	char	*tmp;

	*edit->current = move_first(*edit->current, &edit->curseur);
	ansi("CL_END", 0, STDIN_FILENO);
	ft_strdel(&(*(edit->histo))->line);
	free_tline(*edit->current);
	*edit->current = str_to_line(buf, edit->prompt_len, &edit->curseur);
	tmp = line_to_str(*edit->current);
	(*edit->histo)->line = ft_strdup(tmp);
	ft_putstr_fd(tmp, STDIN_FILENO);
	ft_strdel(&tmp);
	while ((*edit->current)->next)
		*edit->current = (*edit->current)->next;
	return (*edit->current);
}

char	*add_char_str(char *look, char c)
{
	char	*tmp;

	tmp = NULL;
	if (!look)
	{
		if (!(look = ft_strnew(1)))
			return (NULL);
		look[0] = c;
		return (look);
	}
	else
	{
		if (!(tmp = ft_strnew(ft_strlen(look) + 1)))
			return (NULL);
		tmp = ft_strcpy(tmp, look);
		tmp[ft_strlen(look)] = c;
		ft_strdel(&look);
		return (tmp);
	}
}

char			lookup_history(t_edit *edit)
{
	char	*look;
	char	*str;
	char	c;

	c = 0;
	str = NULL;
	look = NULL;
	init_lookup(edit);
	while (read(STDIN_FILENO, &c, 1))
	{
		if (c != ' ' && (!ft_isalnum(c) || c == '\n') && c != 127 && c != 8)
		{
			ft_strdel(&look);
			return (reset(edit, c));
		}
		else if (c != 127 && c != 8)
		{
			if ((str = search_hist(edit, look, c)))
			{
				look = add_char_str(look, c);
				*edit->current = clear(edit, str);
				ft_strdel(&str);
			}
		}
	}
	return (0);
}
