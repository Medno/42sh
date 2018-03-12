/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tline2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 11:29:54 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/12 15:13:18 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

t_line	*str_to_line(char *str, int prompt, t_curs *curseur)
{
	t_line	*cur;

	cur = create_elem(0, prompt + 1);
	while (str && *str && *(str + 1))
	{
		push_new(cur, *str, curseur);
		str++;
	}
	return (cur);
}

char	*line_to_str(t_line *cur)
{
	char	*str;
	int		i;

	if (!cur->prev && !cur->next && !cur->c)
		return (NULL);
	if (!(str = malloc(sizeof(char) * full_tline_len(cur) + 1)))
		return (NULL);
	i = 0;
	while (cur->prev)
		cur = cur->prev;
	while (cur->next)
	{
		str[i] = cur->c;
		cur = cur->next;
		i++;
	}
	str[i] = 0;
	return (str);
}

void	increment_all(t_line *current, t_curs *curseur, int c)
{
	t_line	*tmp;

	tmp = current;
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

int		parted_tline_len(t_line *cur)
{
	int		i;

	i = 0;
	while (cur)
	{
		i++;
		cur = cur->next;
	}
	return (i);
}

void	ft_clean_edit(t_edit *edit)
{
	if (edit)
	{
		ft_strdel(&(edit->comp->dir));
		ft_strdel(&(edit->comp->str));
		ft_strdel(&(edit->comp->cmd));
		edit->comp->current = NULL;
		if (edit->comp->list)
		{
			ft_clean_lcomp_list(edit->comp->list);
			edit->comp->list = NULL;
		}
		free(edit->comp);
		edit->comp = NULL;
	}
}
