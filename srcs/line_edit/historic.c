/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   historic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 08:28:30 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/12 12:27:54 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

t_line	*hist_up(t_line *cur, t_hist *histo, int prompt, t_curs *curseur)
{
	cur = moove_first(cur, prompt, curseur);
	ft_strdel(&histo->line);
//	histo->line = go_str(cur);
	dblist_free(cur);
	if (histo->prev)
		histo = histo->prev;
// str_to_line(histo->line);		
	return (/*new_list*/);
}
