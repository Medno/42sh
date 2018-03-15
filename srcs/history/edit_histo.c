/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_histo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 15:25:37 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/15 15:04:50 by kyazdani         ###   ########.fr       */
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
	while ((*histo)->next)
		*histo = (*histo)->next;
	ft_strdel(&(*histo)->line);
	(*histo)->line = line_to_str(cur);
}

t_line	*hist_up(t_line *cur, t_hist **histo, int prompt, t_curs *curseur)
{
	char	*tmp;

	if (!*histo || !(*histo)->prev)
		return (cur);
	cur = move_first(cur, curseur);
	ansi("CL_END", 0, STDIN_FILENO);
	ft_strdel(&(*histo)->line);
	(*histo)->line = line_to_str(cur);
	(*histo)->line = ft_strjoindel((*histo)->line, "\n");
	free_tline(cur);
	if ((*histo)->prev)
		*histo = (*histo)->prev;
	cur = str_to_line((*histo)->line, prompt, curseur);
	tmp = line_to_str(cur);
	ft_putstr_fd(tmp, STDIN_FILENO);
	ft_strdel(&tmp);
	return (cur);
}

t_line	*hist_down(t_line *cur, t_hist **histo, int prompt, t_curs *curseur)
{
	char	*tmp;

	if (!*histo || !(*histo)->next)
		return (cur);
	cur = move_first(cur, curseur);
	ansi("CL_END", 0, STDIN_FILENO);
	ft_strdel(&(*histo)->line);
	(*histo)->line = line_to_str(cur);
	(*histo)->line = ft_strjoindel((*histo)->line, "\n");
	free_tline(cur);
	if ((*histo)->next)
		*histo = (*histo)->next;
	cur = str_to_line((*histo)->line, prompt, curseur);
	tmp = line_to_str(cur);
	ft_putstr_fd(tmp, STDIN_FILENO);
	ft_strdel(&tmp);
	return (cur);
}
