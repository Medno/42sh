/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 14:13:26 by kyazdani          #+#    #+#             */
/*   Updated: 2018/04/16 12:22:30 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	increme_all(t_hist *cur, int c)
{
	t_hist	*tmp;

	tmp = cur;
	while (tmp)
	{
		tmp->nb += c;
		tmp = tmp->next;
	}
}

static void	free_elem(t_hist *tmp, t_hist **histo)
{
	t_hist	*tmp2;

	if (!tmp)
		return ;
	increme_all(tmp->next, -1);
	tmp2 = tmp->prev;
	if (tmp2)
		tmp2->next = tmp->next;
	tmp2 = tmp->next;
	if (tmp2)
		tmp2->prev = tmp->prev;
	else if (!(*histo)->next && (*histo)->prev)
		*histo = (*histo)->prev;
	tmp->next = NULL;
	tmp->prev = NULL;
	ft_strdel(&tmp->line);
	if (!(*histo)->next && !(*histo)->prev)
		ft_memdel((void **)&(*histo));
	else
		ft_memdel((void **)&tmp);
}

int			free_offset_hist(t_hist **histo, char *offset)
{
	int		nb;
	t_hist	*tmp;

	nb = ft_atoi(offset);
	if (nb <= 0 || ft_strlen(offset) >= 10)
	{
		ft_printf_fd(2, "42sh: history: %s: history position out of range\n",
				offset);
		return (1);
	}
	tmp = *histo;
	while (tmp && tmp->prev)
		tmp = tmp->prev;
	while (tmp && nb != tmp->nb)
		tmp = tmp->next;
	if (!tmp)
	{
		ft_printf_fd(2, "42sh: history: %s: history position out of range\n",
				offset);
		return (1);
	}
	else
		free_elem(tmp, histo);
	return (0);
}

int			free_history(t_hist **histo)
{
	t_hist	*tmp;

	if (!*histo)
		return (0);
	while ((*histo) && (*histo)->prev)
		*histo = (*histo)->prev;
	while (*histo)
	{
		if (!(*histo)->next)
			break ;
		tmp = *histo;
		*histo = (*histo)->next;
		(*histo)->prev = NULL;
		tmp->next = NULL;
		ft_strdel(&tmp->line);
		ft_memdel((void **)&tmp);
	}
	ft_strdel(&(*histo)->line);
	ft_memdel((void **)&(*histo));
	return (0);
}
