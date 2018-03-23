/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookup_historic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 10:05:33 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/23 10:48:25 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

t_line		*lookup_history(t_edit *edit)
{
	char	buf;

	buf = 0;
	*edit->current = move_first(*edit->current, &edit->curseur);
	ansi("LE", edit->prompt_len + 1, STDIN_FILENO);
	ansi("CL_END", 0, STDIN_FILENO);
	ft_putstr_fd("(reverse-i-search):", STDIN_FILENO);
	while (read(STDIN_FILENO, &buf, 1))
	{
		if (buf == 27)
		{
			ansi("LE", 50, STDIN_FILENO);
			ansi("CL_END", 0, STDIN_FILENO);
			return (ft_line_esc(*edit->current, put_path(&edit->env),
						&edit->curseur, edit->histo));
		}
	}
	return (*edit->current);
}
