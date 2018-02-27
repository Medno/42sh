/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   historic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 08:28:30 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/27 15:55:46 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

void	init_hist(t_hist **histo)
{
	t_hist	*new;

	new = create_hist("");
	if (!*histo)
		*histo = new;
	else
	{
		while ((*histo)->next)
			*histo = (*histo)->next;
		new->prev = *histo;
		(*histo)->next = new;
		*histo = new;
	}
}

void	handle_history_ret(t_line *cur, t_hist **histo)
{
	t_hist	*tmp;

	while ((*histo)->next)
		*histo = (*histo)->next;
	if (!cur->next && !cur->prev && !cur->c)
	{
		if (!(*histo)->prev)
			ft_memdel((void **)histo);
		else
		{
			*histo = (*histo)->prev;
			tmp = (*histo)->next;
			(*histo)->next = NULL;
			tmp->prev = NULL;
			ft_memdel((void **)&tmp);
		}
	}
	else
	{
		ft_strdel(&(*histo)->line);
		(*histo)->line = line_to_str(cur);
	}
}

t_line	*str_to_line(char *str, int prompt, t_curs *curseur)
{
	t_line	*new;

	new = create_elem(0);
	while (str && *str)
	{
		push_new(new, *str, prompt, curseur);
		str++;
	}
	return (new);
}

t_line	*hist_up(t_line *cur, t_hist **histo, int prompt, t_curs *curseur)
{
	if (!*histo || !(*histo)->prev)
		return (cur);
	cur = moove_first(cur, prompt, curseur);
	ft_printf("\033[J");
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
	cur = moove_first(cur, prompt, curseur);
	ft_printf("\033[J");
	ft_strdel(&(*histo)->line);
	(*histo)->line = line_to_str(cur);
	free_dblist(cur);
	if ((*histo)->next)
		*histo = (*histo)->next;
	cur = str_to_line((*histo)->line, prompt, curseur);
	return (cur);
}
