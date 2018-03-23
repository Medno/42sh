/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookup_historic2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 13:21:32 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/23 16:00:33 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

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
	if (!tmp)
		return (NULL);
	else
		return (ft_strdup(tmp->line));
}
