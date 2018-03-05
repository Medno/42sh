/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 12:18:25 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/05 12:05:50 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	paste_last_hist(t_hist **histo)
{
	t_hist	*tmp;

	tmp = NULL;
	if (!(*histo)->prev)
	{
		tmp = malloc(sizeof(t_hist));
		tmp->line = NULL;
		tmp->next = NULL;
		tmp->prev = *histo;
		(*histo)->next = tmp;
	}
	else if (!ft_strchr((*histo)->prev->line, '\n'))
		;
	else
	{
		(*histo) = (*histo)->prev;
		tmp = (*histo)->next;
	}
	(*histo)->line = ft_strjoindel((*histo)->line, "\n");
	if (tmp && tmp->line)
		(*histo)->line = ft_strjoindel((*histo)->line, tmp->line);
	(*histo)->next = NULL;
	ft_strdel(&tmp->line);
	ft_memdel((void **)&tmp);
}
