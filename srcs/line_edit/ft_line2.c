/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 09:12:41 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/13 09:17:22 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

t_line		*ft_line_usual(t_line *current, char c, int prompt, t_curs *curseur)
{
	if (c == 127 || c == 8)
		current = line_delone(current, prompt, curseur);
	else if (c == '\t' || (c == 4 && !current->next))
		current = completion(current, prompt, curseur);
	else if (c == 4)
		current = del_next(current);
	else if (c == 1)
		current = moove_first(current, prompt, curseur);
	else if (c == 2)
		current = moove_left(current, prompt, curseur);
	else if (c == 5)
		current = moove_last(current, prompt, curseur);
	else if (c == 6)
		current = moove_right(current, prompt, curseur);
	else if (c == 7)
		;//enter select mode (for pasting) // CTRL_G
	else if (c == 22)
		;//paste // CTRL_V
	else if (c == 11)
		;//del all after cursor and put into char to paste // CTRL_K
	else if (c == 21)
		;//del all line and copy it into char to paste // CTRL_U
	else if (c >= 32 && c <= 126)
		current = push_new(current, c, prompt, curseur);
	return (current);
}
