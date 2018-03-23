/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookup_historic2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 13:21:32 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/23 15:12:37 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

char	*strstrall(char *s, char *look)
{
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

char	*search_hist(t_edit *edit, char *look, char c)
{
	t_hist	*tmp;
	char	*s;

	tmp = *edit->histo;
	s = NULL;
	if (look)
		s = ft_strdup(look);
	s = add_char_str(s, c);
	while (tmp->next)
		tmp = tmp->next;
	while (tmp && !strstrall(tmp->line, s))
		tmp = tmp->prev;
	if (!tmp)
		return (NULL);
	else
		return (ft_strdup(tmp->line));
}
