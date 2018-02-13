/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pasting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 16:18:24 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/13 16:34:32 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

t_line			*paste(t_line *cur, char *str, int prompt, t_curs *curseur)
{
	while (str && *str)
	{
		cur = push_new(cur, *str, prompt, curseur);
		str++;
	}
	return (cur);
}
