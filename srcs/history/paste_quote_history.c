/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paste_quote_history.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 15:29:48 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/06 11:35:23 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	check_last_char(char *str)
{
	while (*str)
		str++;
	str--;
	if (*str == '\n')
		return (1);
	else
		return (0);
}

void		paste_last_hist(t_hist **histo)
{
	t_hist	*tmp;

	(*histo) = (*histo)->prev;
	if (!check_last_char((*histo)->line))
		(*histo)->line = ft_strjoindel((*histo)->line, "\n");
	tmp = (*histo)->next;
	(*histo)->line = ft_strjoindel((*histo)->line, tmp->line);
	(*histo)->next = NULL;
	ft_strdel(&tmp->line);
	ft_memdel((void **)&tmp);
}
