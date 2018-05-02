/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_l.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 13:44:05 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/05 13:54:16 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

t_line	*clearscreen(t_edit *edit, t_init init)
{
	char	*str;

	ft_putstr_fd("\033[H", STDIN_FILENO);
	ansi("CL_END", 0, STDIN_FILENO);
	put_path(&init);
	str = line_to_str(*edit->current);
	ft_putstr_fd(str, STDIN_FILENO);
	ft_strdel(&str);
	while ((*edit->current)->next)
		*edit->current = (*edit->current)->next;
	return (*edit->current);
}
