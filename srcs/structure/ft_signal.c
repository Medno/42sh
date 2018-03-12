/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 10:14:23 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/12 16:36:36 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void			sigint_prompt(void)
{
	int		x;

	*g_ed->current = move_last(*g_ed->current, &g_ed->curseur);
	write(0, "\n", 1);
	ft_strdel(&g_in->str);
	free_tline(*g_ed->current);
	ft_clean_edit(g_ed);
	x = put_path(&g_in->new_env);
	ft_line_edition(&g_in->str, x, &g_in->historic, g_in->new_env);
	signal(SIGINT, (void (*)(int))sigint_prompt);
}

void	sig_write_nl(void)
{
	write(1, "\n", 1);
	signal(SIGINT, SIG_IGN);
}
