/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 10:08:45 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/11 12:59:37 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			ft_env(t_init *init, char ***entry)
{
	(void)init;
	(void)entry;
	/*juste pour test */
	ft_print_env(init->new_env);
	return (0);
}
