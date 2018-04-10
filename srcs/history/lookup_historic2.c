/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookup_historic2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 13:21:32 by kyazdani          #+#    #+#             */
/*   Updated: 2018/04/10 11:31:54 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

t_line	*clear(t_edit *edit, char *buf)
{
	char	*tmp;

	*edit->current = move_first(*edit->current, &edit->curseur);
	ansi("CL_END", 0, STDIN_FILENO);
	ft_strdel(&(*(edit->histo))->line);
	free_tline(*edit->current);
	*edit->current = str_to_line(buf, edit->prompt_len, &edit->curseur);
	tmp = line_to_str(*edit->current);
	if (tmp)
	{
		(*edit->histo)->line = ft_strdup(tmp);
		ft_putstr_fd(tmp, STDIN_FILENO);
		ft_strdel(&tmp);
	}
	return (*edit->current);
}

char	*strstrall(char *s, char *look)
{
	if (!s || !look)
		return (NULL);
	while (*s)
	{
		if (*s == *look)
		{
			if (!ft_strncmp(s, look, ft_strlen(look)))
				return (s);
		}
		s++;
	}
	return (NULL);
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

char	*search_hist(t_edit *edit, char *look, char c)
{
	t_hist	*tmp;
	char	*s;

	tmp = *edit->histo;
	s = NULL;
	if (look)
		s = ft_strdup(look);
	s = add_char_str(s, c);
	while (tmp->next && tmp->next->next)
		tmp = tmp->next;
	while (tmp && tmp->line && !strstrall(tmp->line, s))
		tmp = tmp->prev;
	ft_strdel(&s);
	if (!tmp || !tmp->line)
		return (NULL);
	else
		return (ft_strdup(tmp->line));
}
