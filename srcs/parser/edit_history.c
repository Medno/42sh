/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 12:18:25 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/02 12:46:54 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	paste_last_hist(t_hist **histo)
{
	t_hist	*tmp;

	(*histo) = (*histo)->prev;
	tmp = (*histo)->next;
	(*histo)->line = ft_strjoindel((*histo)->line, "\n");
	(*histo)->line = ft_strjoindel((*histo)->line, tmp->line);
	(*histo)->next = NULL;
	ft_strdel(&tmp->line);
	ft_memdel((void **)&tmp);
}
