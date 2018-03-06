/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_histo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 15:25:37 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/06 11:14:37 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

void	init_hist(t_hist **histo)
{
	t_hist	*new;

	new = create_hist("");
	if (!*histo)
	{
		*histo = new;
		new->nb = 1;
	}
	else
	{
		while ((*histo)->next)
			*histo = (*histo)->next;
		new->prev = *histo;
		new->nb = (*histo)->nb + 1;
		(*histo)->next = new;
		*histo = new;
	}
}

void	handle_history_ret(t_line *cur, t_hist **histo)
{
	t_hist	*tmp;

	while ((*histo)->next)
		*histo = (*histo)->next;
	ft_strdel(&(*histo)->line);
	if (!cur->next && !cur->prev && !cur->c)
	{
		if (!(*histo)->prev)
			ft_memdel((void **)histo);
		else
		{
			if (g_quote)
			{
				(*histo)->line = ft_strdup("\n");
				return; 
			}
			tmp = *histo;
			*histo = (*histo)->prev;
			(*histo)->next = NULL;
			ft_memdel((void **)&tmp);
		}
	}
	else
		(*histo)->line = line_to_str(cur);
}

t_line	*str_to_line(char *str, int prompt, t_curs *curseur)
{
	t_line	*cur;

	cur = create_elem(0, prompt + 1);
	while (str && *str)
	{
		push_new(cur, *str, curseur);
		str++;
	}
	return (cur);
}

t_line	*hist_up(t_line *cur, t_hist **histo, int prompt, t_curs *curseur)
{
	if (!*histo || !(*histo)->prev)
		return (cur);
	cur = moove_first(cur, curseur);
	ansi("CL_END", 0, STDIN_FILENO);
	ft_strdel(&(*histo)->line);
	(*histo)->line = line_to_str(cur);
	free_dblist(cur);
	if ((*histo)->prev)
		*histo = (*histo)->prev;
	cur = str_to_line((*histo)->line, prompt, curseur);
	return (cur);
}

t_line	*hist_down(t_line *cur, t_hist **histo, int prompt, t_curs *curseur)
{
	if (!*histo || !(*histo)->next)
		return (cur);
	cur = moove_first(cur, curseur);
	ansi("CL_END", 0, STDIN_FILENO);
	ft_strdel(&(*histo)->line);
	(*histo)->line = line_to_str(cur);
	free_dblist(cur);
	if ((*histo)->next)
		*histo = (*histo)->next;
	cur = str_to_line((*histo)->line, prompt, curseur);
	return (cur);
}
