/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 10:14:23 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/09 10:14:38 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	sig_write_nl(int x)
{
	(void)x;
	write(1, "\n", 1);
	signal(SIGINT, SIG_IGN);
}
