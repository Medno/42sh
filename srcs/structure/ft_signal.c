/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 10:14:23 by kyazdani          #+#    #+#             */
/*   Updated: 2018/04/10 10:29:20 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	sig_write_nl(void)
{
	write(1, "\n", 1);
	signal(SIGINT, SIG_IGN);
}

void	catch_and_reset(int sig)
{
	ft_cfmakeinit(&g_in->current);
	hist_to_file(g_in->historic);
	ft_strdel(&g_in->str);
	free_list(&g_in->new_env);
	signal(sig, SIG_DFL);
	kill(0, sig);
}
