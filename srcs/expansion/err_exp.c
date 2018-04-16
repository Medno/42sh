/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_exp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 15:00:28 by pchadeni          #+#    #+#             */
/*   Updated: 2018/04/16 12:23:46 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

char	*err_dollar(t_init *init, char *str)
{
	init->dollar = 1;
	ft_printf_fd(2, "42sh: %s: bad substitution\n", str);
	return (NULL);
}
