/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 10:14:23 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/09 14:17:01 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void			sigint_prompt(int x)
{
	edit_end(&g_in->str, g_ed);
	ft_strdel(&g_in->str);
	step_1(*g_in);
	signal(SIGINT, (void (*)(int))sigint_prompt);
	(void)x;
}

void	sig_write_nl(int x)
{
	(void)x;
	write(1, "\n", 1);
	signal(SIGINT, SIG_IGN);
}
