/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookup_historic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 10:05:33 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/23 11:30:11 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

static char	reset(t_edit *edit, char c)
{
	if (c == 27)
	{
		ansi("LE", 50, STDIN_FILENO);
		ansi("CL_END", 0, STDIN_FILENO);
	}
	else if (c == 4)
		write(STDIN_FILENO, "\n", 1);
	if (c != 3)
		put_path(&edit->env);
	return (c);
}

char		lookup_history(t_edit *edit)
{
	char	c;

	c = 0;
	*edit->current = move_first(*edit->current, &edit->curseur);
	ansi("LE", edit->prompt_len + 1, STDIN_FILENO);
	ansi("CL_END", 0, STDIN_FILENO);
	ft_putstr_fd("(reverse-i-search): ", STDIN_FILENO);
	while (read(STDIN_FILENO, &c, 1))
	{
		if (c == 27)
			return (reset(edit, c));
		else if (c == 3)
			return (reset(edit, c));
		else if (c == 4)
			return (reset(edit, c));
	}
	return (0);
}
