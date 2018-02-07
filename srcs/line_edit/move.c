/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 14:47:01 by pchadeni          #+#    #+#             */
/*   Updated: 2018/02/07 14:49:29 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

t_line		*move_left(t_line *cur)
{
	if (cur->prev)
	{
		tputs(tgetstr("le", NULL), 0, ft_inputchar);
		cur = cur->prev;
	}
	return (cur);
}

t_line		*move_right(t_line *cur)
{
	if (cur->next)
	{
		tputs(tgetstr("nd", NULL), 0, ft_inputchar);
		cur = cur->next;
	}
	return (cur);
}
